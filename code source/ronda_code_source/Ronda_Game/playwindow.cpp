#include "playwindow.h"
#include "ui_playwindow.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

#include <iterator>
#include <vector>

#include <QTime>

#include <QtMultimedia>

#include "scene.h"
#include "deck.h"
#include "table.h"
#include "hand.h"
#include "card.h"
#include "score.h"
#include "info.h"
#include "button.h"

//function that give a delay in ms
void delay(qreal delay)
{
    QTime dieTime= QTime::currentTime().addMSecs(delay);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,10000);
}

//playWindow constructor
PlayWindow::PlayWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowFullScreen);// set wiindow to fullscreen
    setWindowTitle("Ronda Beta V0.4"); //set title
    x=width(); //set widget value (width)
    y=height();//set widget value (height)

    // set up the main scene
    scene = new Scene();
    scene->waiting=false; //scene isnt waiting for player to pick a card
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(-x/2,-y/2,x,y); // position of the scene , size

    //set up the background
    QGraphicsPixmapItem * background = new QGraphicsPixmapItem(QPixmap(":/backgrounds/imgs/BG.png"));
    scene->addItem(background);
    background->setPos(QPointF(-background->boundingRect().width()/2,-background->boundingRect().height()/2)); //set up the position of the background

    //set up audio
    slideAudio = new QMediaPlayer;//sliding card audio
    QAudioOutput *audioOutputslide = new QAudioOutput;
    slideAudio->setAudioOutput(audioOutputslide);
    slideAudio->setSource(QUrl("qrc:/audio/audio/fffet.wav"));

    backgroundMusic = new QMediaPlayer();//background music
    QAudioOutput *audioOutputbg = new QAudioOutput;
    backgroundMusic->setAudioOutput(audioOutputbg);
    backgroundMusic->setSource(QUrl("qrc:/audio/audio/bg_music.wav"));
    audioOutputbg->setVolume(0.02); //background volume set to low value
    backgroundMusic->setLoops(QMediaPlayer::Infinite);
    muted = false;//background music is enabled by default

    //set up info (text to give information)
    startText=new Info(scene,"GAME STARTED !");
    startText->setPos(QPointF(-startText->boundingRect().width()/2,-startText->boundingRect().height()/2));
    scene->addItem(startText);

    turnText=new Info(scene,"IT'S YOUR TURN ! PICK A CARD...");
    turnText->setPos(QPointF(0,y*0.25)+QPointF(-turnText->boundingRect().width()/2,-turnText->boundingRect().height()/2));
    scene->addItem(turnText);

    addText=new Info(scene,"");
    setFont(QFont("Segoe UI Black",scene->width()*0.03));
    scene->addItem(addText);

    gameoverText = new Info(scene,"");
    setFont(QFont("Segoe UI Black",scene->width()*0.03));
    scene->addItem(gameoverText);
}

PlayWindow::~PlayWindow()
{
    delete ui;
}

//function to call to start the game
void PlayWindow::startgame()
{
    qInfo("Game started"); //game started info

    //start background music
    backgroundMusic->play();

    //set up the ui buttons
    Button *closeBt=new Button(this,scene,1);
    closeBt->setPos(QPointF(x/2-closeBt->boundingRect().width(),-y/2)+QPointF(-10,10));
    scene->addItem(closeBt);

    Button *returnBt=new Button(this,scene,2);
    returnBt->setPos(closeBt->pos()+QPointF(-10,0)+QPointF(-returnBt->boundingRect().width(),0));
    scene->addItem(returnBt);

    Button *muteBt=new Button(this,scene,3);
    muteBt->setPos(returnBt->pos()+QPointF(-10,0)+QPointF(-muteBt->boundingRect().width(),0));
    scene->addItem(muteBt);

    //set up deck
    Deck *deck = new Deck(scene);
    deck->setPos(QPointF(-x*0.425,0)+QPointF(-deck->boundingRect().width()/2,-deck->boundingRect().height()/2));//set position of the deck
    scene->addItem(deck);

    //set up player score ui
    playerScore=new Score(scene,1);
    opScore=new Score(scene,0);
    scene->addItem(playerScore);
    scene->addItem(opScore);
    playerScore->setPos(QPointF(-x*0.35,y*0.55 - playerScore->boundingRect().height()/2)+QPointF(-playerScore->boundingRect().width()/2,-playerScore->boundingRect().height()/2));
    opScore->setPos(QPointF(-x*0.35,-y*0.55 + opScore->boundingRect().height()/2)+QPointF(-opScore->boundingRect().width()/2,-opScore->boundingRect().height()/2));

    //set up player/op hand and table
    hand = new Hand(scene);
    op= new Hand(scene);
    table = new Table(scene);
    deck->shuffle(); //shuffle cards vector in deck

    //show/hide "Game started" text
    startText->startAnimation();
    delay(1000);//keep the text for 1sec
    startText->startAnimation();

    for(int i=0;i<5;i++) round(deck,hand,op); //start rounds (5 round in the game)

    delay(500);//delay between last round end and clearing the table

    //collecting romaining cards
    if(!table->cardsHand.isEmpty())
    {
        if(lastcolledted){ //by the player
            for (int k=1;k<=table->cardsHand.size();k++)
                table->cardsHand[k-1]->startAnim(QPointF(-x/3,y/2),k*50 +600);
            playerScore->value += table->cardsHand.size(); //adding romaining cards to the player score
        }
        else { //by the op
            for (int k=1;k<=table->cardsHand.size();k++)
                table->cardsHand[k-1]->startAnim(QPointF(-x/3,-y*0.7 ),k*50 +600);
            opScore->value += table->cardsHand.size();//adding romaining cards to the player score
        }

        //updating scores
        playerScore->updateScore();
        opScore->updateScore();
    }

    //setting up game end texts
    if(playerScore->value>20) gameoverText->setText("GREAT JOB , YOU WON !!");
    else if(playerScore->value<20) gameoverText->setText("GAME OVER ! YOU LOST , GOODLUCK NEXT TIME...");
    else if(playerScore->value==20) gameoverText->setText("GAME OVER , IT'S A DRAW !!");
    gameoverText->setPos(QPointF(-gameoverText->boundingRect().width()/2,-gameoverText->boundingRect().height()/2));
    gameoverText->startAnimation();

    qInfo() << "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeend :=)";//game over info
}

//fonction to play a round
void PlayWindow::round(Deck *deck, Hand *hand, Hand *op){

    //get 4 radnom cards in player hand
    for(int i=0;i<4;i++){

        delay(300); //give a delay to draw each card
        hand->addCard(deck->drawCard()); //draw card from deck and add it to player's hand

        //set up drawing cards animation
        hand->cardsHand[i]->posAnimation->setStartValue(QPointF(-x*0.425,0)+QPointF(-hand->cardsHand[i]->boundingRect().width()/2,-hand->cardsHand[i]->boundingRect().height()/2)); //start card animation from deck position
        hand->cardsHand[i]->posAnimation->setEndValue(QPointF(-x*0.175 + i*x*0.116, y*0.4)+QPointF(-hand->cardsHand[i]->boundingRect().width()/2,-hand->cardsHand[i]->boundingRect().height()/2)); //end card animation in the free positon in hand
        hand->cardsHand[i]->posAnimation->setDuration(500 + i*100); //duration of animation

        hand->cardsHand[i]->setHand(1); //set the cards "whichHand" to 1=player hand

        scene->addItem(hand->cardsHand[i]);

        hand->cardsHand[i]->posAnimation->start(); // start the animation

        //start slide audio
        slideAudio->setPosition(0);
        slideAudio->play();
    }

    delay(300); //delay between drawing cards for player and for op

    //get 4 radnom cards in opponent hand
    for(int i=0;i<4;i++){

        delay(300);
        op->addCard(deck->drawCard());

        //set up drawing cards animation
        op->cardsHand[i]->posAnimation->setStartValue(QPointF(-x*0.425,0)+QPointF(-op->cardsHand[i]->boundingRect().width()/2,-op->cardsHand[i]->boundingRect().height()/2));
        op->cardsHand[i]->posAnimation->setEndValue(QPointF(-x*0.175 + i*x*0.116, -y*0.4)+QPointF(-op->cardsHand[i]->boundingRect().width()/2,-op->cardsHand[i]->boundingRect().height()/2));
        op->cardsHand[i]->posAnimation->setDuration(500 + i*100);

        scene->addItem(op->cardsHand[i]);

        op->cardsHand[i]->posAnimation->start();

        //start slide audio
        slideAudio->setPosition(0);
        slideAudio->play();
    }

    //removing image from the deck if its empty
    if(deck->cardsDeck.size() ==0) scene->removeItem(deck);

    delay(300); //delay between drawing cards for op and flipping player cards

    //boucle to flip all player cards
    for(int i=0;i<4;i++)
    {
        delay(500); //delay between flipping each card
        hand->cardsHand[i]->flip(); //flip card

        //start slide audio
        slideAudio->setPosition(0);
        slideAudio->play();
    }

    //4 turns for each player
    for (int i = 0; i < 4; i++){
        playerturn(hand,1); //call playerturn function to start player turn
        playerturn(op,0);//call playerturn function to start op turn
    }
}

//function to call to start player turn
void PlayWindow::playerturn(Hand *playingHand,int isPlayerturn){

    scene->selectedCard=nullptr;//set selected card to null
    selectcard(isPlayerturn);//calling function to select a card

    //check if the selected card has a match in the table
    if(table->checkCard(scene->selectedCard)!=nullptr){

        lastcolledted = isPlayerturn;

        Card*foundCard = table->checkCard(scene->selectedCard);
        scene->selectedCard->setZValue(2);
        foundCard->setZValue(1);

        //selected card animation to the matching card
        scene->selectedCard->startAnim(foundCard->pos(),500);

        //start slide audio
        slideAudio->setPosition(0);
        slideAudio->play();

        table->freePos(foundCard->pos() + QPointF(foundCard->boundingRect().width()/2,foundCard->boundingRect().height()/2));
        playingHand->dropCard(scene->selectedCard);
        table->dropCard(foundCard);

        //set up a Hand for collected cards until they are added to score
        Hand *playerCollected = new Hand(scene);
        playerCollected->addCard(scene->selectedCard);
        playerCollected->addCard(foundCard);

        //going up animation
        delay(600);
        scene->selectedCard->startAnim(scene->selectedCard->pos() + QPointF(0,-10),150);
        foundCard->startAnim(foundCard->pos() + QPointF(0,-20),250);

        //going down animation
        delay(300);
        scene->selectedCard->startAnim(scene->selectedCard->pos() + QPointF(0,10));
        foundCard->startAnim(foundCard->pos() + QPointF(0,20));

        delay(350);

        //check if there is more cards to collect
        for (int i=scene->selectedCard->getNumber()+1; i<10 ; i++)
        {
            if(table->cardsHand.size() == 0) break; //table is empty = no more cards to collect

            bool found=false;
            for(int j=0;j<table->cardsHand.size();j++)
            {
                if(table->cardsHand[j]->getNumber() == i){

                    found = true;
                    //animlation to the next card
                    for (int k=0;k<playerCollected->cardsHand.size();k++) {
                        playerCollected->cardsHand[k]->setZValue(40-k);
                        playerCollected->cardsHand[k]->startAnim(table->cardsHand[j]->pos(),k*50+500);
                    }
                    //start slide audio
                    slideAudio->setPosition(0);
                    slideAudio->play();


                    table->cardsHand[j]->setZValue(40-playerCollected->cardsHand.size());
                    delay(playerCollected->cardsHand.last()->posAnimation->duration()+100);
                    playerCollected->addCard(table->cardsHand[j]);
                    table->freePos(table->cardsHand[j]->pos() + QPointF(table->cardsHand[j]->boundingRect().width()/2,table->cardsHand[j]->boundingRect().height()/2));
                    table->dropCard(table->cardsHand[j]);

                    //collecting card jumping animations
                    for (int k=1;k<=playerCollected->cardsHand.size();k++) playerCollected->cardsHand[k-1]->startAnim(playerCollected->cardsHand[k-1]->pos() + QPointF(0,-k*10),k*100+50);
                    delay(playerCollected->cardsHand.last()->posAnimation->duration()+50);
                    for (int k=1;k<=playerCollected->cardsHand.size();k++) playerCollected->cardsHand[k-1]->startAnim(playerCollected->cardsHand[k-1]->pos() + QPointF(0,k*10));
                    delay(playerCollected->cardsHand.last()->posAnimation->duration()+100);

                    break;
                }
            }
            //break if the next card (number) isnt found
            if(!found) break;
        }

        //cards animation to the collector hand
        if(isPlayerturn)
            for (int k=1;k<=playerCollected->cardsHand.size();k++) {
                playerCollected->cardsHand[k-1]->startAnim(QPointF(-x/3,y/2),k*50 +600);
                //start slide audio
                slideAudio->setPosition(0);
                slideAudio->play();
            }
        else
            for (int k=1;k<=playerCollected->cardsHand.size();k++) {
                playerCollected->cardsHand[k-1]->startAnim(QPointF(-x/3,-y*0.7 ),k*50 +600);
                //start slide audio
                slideAudio->setPosition(0);
                slideAudio->play();
            }

        lastcolledted = isPlayerturn;

        //adding collected cards to playaer or op
        qreal yoffset=0.31*y;
        if(isPlayerturn) {
            playerScore->value += playerCollected->cardsHand.size();
            yoffset = -yoffset;
        }
        else
            opScore->value += playerCollected->cardsHand.size();

        //updating scores
        playerScore->updateScore();
        opScore->updateScore();

        //setting up collected score info
        QString txt = "+";
        addText->setText(txt.append(QString::number(playerCollected->cardsHand.size())));
        addText->setPos(QPointF(-addText->boundingRect().width()/2,-addText->boundingRect().height()/2)+QPointF(-x*0.325,-yoffset));
        addText->startAnimation();
        delay(1000);
        addText->startAnimation();
    }

    //no matching card in the table
    else {
        table->addCard(scene->selectedCard);
        playingHand->dropCard(scene->selectedCard);

        //animation to the free position in table
        scene->selectedCard->startAnim(table->emptyPos[0]+QPointF(-scene->selectedCard->boundingRect().width()/2,-scene->selectedCard->boundingRect().height()/2),500);

        //start slide audio
        slideAudio->setPosition(0);
        slideAudio->play();

        table->fillPos(table->emptyPos[0]);

        delay(550);
    }
}

//select a card to play the turn
void PlayWindow::selectcard(int isPlayerturn)
{
    //for the player turn
    if(isPlayerturn){

        scene->waiting=true;//wait for the player to pick a card
        turnText->startAnimation();//show turn  text

        //keep the game stopped until the player select a card
        while (scene->selectedCard==nullptr)
            QCoreApplication::processEvents(QEventLoop::AllEvents,10000);

        turnText->startAnimation();//hide player turn
        scene->waiting=false; //stop waiting for the player to pick a card
    }
    //if its the op turn
    else{

        scene->selectedCard=nullptr;

        //select a card depanding on the difficulty
        if(difficulty==0){ //easy
            srand(time(0));
            scene->selectedCard = op->cardsHand[rand() % op->cardsHand.size()];//select a random card
        }

        else if(difficulty == 1){ //hard

            //select a similar card to the one in the table
            for(int i=0;i<op->cardsHand.size();i++){
                bool isSelected = false;
                for(int j=0;j<table->cardsHand.size();j++){
                    if(op->cardsHand[i]->getNumber() == table->cardsHand[j]->getNumber())
                    {
                        scene->selectedCard = op->cardsHand[i];
                        isSelected = true;
                        break;
                    }
                }
                if(isSelected) break;

                //pick a random card if there is no match
                srand(time(0));
                scene->selectedCard = op->cardsHand[rand() % op->cardsHand.size()];//select a random card
            }
        }

        //flip the selected card
        scene->selectedCard->flip();
        delay(300);
    }
}
