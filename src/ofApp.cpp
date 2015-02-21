#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("player one");
   
    
    // imagen de fondo del salpicadero
    bg.loadImage("bg.jpg");
    
    // imagen de fondo con reja y logo
    fondoLogo.loadImage("fondo_reja_con_logo.jpg");
    
    // salpicadero negro con halo
    salpicadero.loadImage("salpicadero_negro.png");
    
    // marcador del coche
    esfera.loadImage("esfera_marcador.png");
    
    // mscara con barras horizontales para la calidad de conexion
    mascaraBarra.loadImage("mascara_barras.png");
    
    // imahen para el final
    winnerImg.loadImage("winner.png");
    
    // inicias el control de la partida
    game.setup("/dev/tty.Bluetooth-Incoming-Port"); //tty.Bluetooth-Incoming-Port //tty.usbmodem1411
    game.startEngines();
    
    // inicias los players diciendole cual es su mindwaves
    playerOne.setup("/dev/tty.MindWaveMobile-DevA", "01");
    playerTwo.setup("/dev/tty.MindWaveMobile-DevA-1", "02");
    
    // cada vez que el coche pasa por el sensor de vuelta se ejecuta este listener
    ofAddListener(game.pasoPorVueltaOne, this, &ofApp::playerOneNewLap);
    ofAddListener(game.pasoPorVueltaTwo, this, &ofApp::playerTwoNewLap);
    
    // si el marcador de vueltas de alguno de loc players llega a 10
    ofAddListener(playerOne.playerWin, this, &ofApp::playerOneWins);
    ofAddListener(playerTwo.playerWin, this, &ofApp::playerTwoWins);
    
    // gui con las posiciones de los servos
    
    gui.setup();
    gui.setName("AJUSTES");
    gui.add(useAttention.setup("useAttention", false));
    gui.add(useMeditation.setup("useMeditation", false));
    gui.add(useBooth.setup("useBooth", false));
    gui.add(playerOne.ajustes);
    gui.add(playerTwo.ajustes);
    gui.loadFromFile("settings.xml");
    
    // pasamos las posiciones al game
    game.ptoServoPlayerOne.set(playerOne.servoMin, playerOne.servoMax);
    game.ptoServoPlayerOne.set(playerTwo.servoMin, playerTwo.servoMax);
    
    // listener para refrescar las posiciones de los servos mientras ajustas, pulsando leer
    ofAddListener(gui.savePressedE, this, &ofApp::guardaGui);
    
    // muestra el gui
    showGui = false;
    
    
    // cargamos el semaforo
    semaforo.setup();
    
    ofAddListener(semaforo.terminado, this, &ofApp::finishedSemaforo);
    ofAddListener(semaforo.cargado, this, &ofApp::loadedSemaforo);
    
    // creamos la segunda ventana pal player 2
    secondWindow.setup("player two", 50, 50, 1920, 1080, false);
 
    // para saber quien ha ganado y dibujarle el win en su apntalla
    whoWins = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // actualiza los players
    playerOne.update();
    
    // actualiza el power de los jugadores
    game.setPlayerOnePower(playerOne.getPlayerPower());
    game.setPlayerTwoPower(playerTwo.getPlayerPower());
    
    // actualizas el juego que manda lo que sea al ardu
    game.update();
    
    // actualiza el semaforo, si no esta running ya pasa el de todo
    semaforo.update();
    
    
   // cout << playerOne.getTiempoTotal() << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){

    // draw players
    drawPlayerOne();
    drawPlayerTwo();
    
    // debug player info
    playerOne.drawDebug(300, 100);
    playerTwo.drawDebug(300, 300);
    
    // debug game status
    game.drawDebug();
    
    // gui
    if(showGui) gui.draw();
}


//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
void ofApp::drawPlayerOne(){
    ////////////////////////////////////////
    ///////// player ONE ///////////////////
    ////////////////////////////////////////
    
    fondoLogo.draw(0, 0); // fondo con reja
    
    if(game.gameStatus != partidaSlot::FINISHED || whoWins != 1){
        
        salpicadero.draw(0, 0); // salpicadero
        // datos del player one
        playerOne.drawPlayerNumber();
        playerOne.drawConcentrationMeditation();
        playerOne.drawlapsData();
    }
    
    ofPoint ptMarcadorUno(377, ofGetHeight()-esfera.getHeight());
    
    // dependiendo del estado de la partida dibujamos
    // el semaforo de la cuenta atras
    // la esfera con el marcador de power
    // el panel de winner
    switch (game.gameStatus) {
        case partidaSlot::READY_TO_RUN:
            esfera.draw(ptMarcadorUno.x,ptMarcadorUno.y); // esfera
            playerOne.drawGauge(ofPoint(945, (ofGetHeight()-esfera.getHeight()) + 508)); // aguja
            break;
            
        case partidaSlot::START_ENGINES:
            esfera.draw(ptMarcadorUno.x,ptMarcadorUno.y); // esfera
            playerOne.drawGauge(ofPoint(945, (ofGetHeight()-esfera.getHeight()) + 508)); // aguja
            
            break;
            
        case partidaSlot::COUNTDOWN:
            
            break;
            
        case partidaSlot::RACING:
            esfera.draw(ptMarcadorUno.x,ptMarcadorUno.y); // esfera
            playerOne.drawGauge(ofPoint(945, (ofGetHeight()-esfera.getHeight()) + 508)); // aguja
            break;
            
        case partidaSlot::FINISHED:
            if(whoWins == 1){
                winnerImg.draw(0, 0);
            }else{
                esfera.draw(ptMarcadorUno.x,ptMarcadorUno.y); // esfera
                playerOne.drawGauge(ofPoint(945, (ofGetHeight()-esfera.getHeight()) + 508)); // aguja
            }
            break;
    }
    
    if(game.gameStatus != partidaSlot::FINISHED || whoWins != 1){
        
        // semaforo, es autonomo si esta funcionando se ve
        semaforo.draw(ptMarcadorUno.x,ptMarcadorUno.y); // semaforo en la misma pos que la esfera
    
    
        playerOne.drawConnection(); // barra de calidad de conexion
        mascaraBarra.draw(0, 0);
    }
}


//--------------------------------------------------------------
void ofApp::drawPlayerTwo(){
    
    secondWindow.begin();
    ////////////////////////////////////////
    ///////// player TWO ///////////////////
    ////////////////////////////////////////
    
    fondoLogo.draw(0, 0); // fondo con reja
    
    if(game.gameStatus != partidaSlot::FINISHED || whoWins != 2){
        salpicadero.draw(0, 0); // salpicadero
    
    
        // datos del player one
        playerTwo.drawPlayerNumber();
        playerTwo.drawConcentrationMeditation();
        playerOne.drawlapsData();
    }
    
    ofPoint ptMarcadorUno(377, ofGetHeight()-esfera.getHeight());
    
    // dependiendo del estado de la partida dibujamos
    // el semaforo de la cuenta atras
    // la esfera con el marcador de power
    // el panel de winner
    switch (game.gameStatus) {
        case partidaSlot::READY_TO_RUN:
            esfera.draw(ptMarcadorUno.x,ptMarcadorUno.y); // esfera
            playerTwo.drawGauge(ofPoint(945, (ofGetHeight()-esfera.getHeight()) + 508)); // aguja
            break;
            
        case partidaSlot::START_ENGINES:
            esfera.draw(ptMarcadorUno.x,ptMarcadorUno.y); // esfera
            playerTwo.drawGauge(ofPoint(945, (ofGetHeight()-esfera.getHeight()) + 508)); // aguja
            
            break;
            
        case partidaSlot::COUNTDOWN:
            
            break;
            
        case partidaSlot::RACING:
            esfera.draw(ptMarcadorUno.x,ptMarcadorUno.y); // esfera
            playerTwo.drawGauge(ofPoint(945, (ofGetHeight()-esfera.getHeight()) + 508)); // aguja
            break;
            
        case partidaSlot::FINISHED:
            if(whoWins == 2){
                winnerImg.draw(0, 0);
            }else{
                esfera.draw(ptMarcadorUno.x,ptMarcadorUno.y); // esfera
                playerTwo.drawGauge(ofPoint(945, (ofGetHeight()-esfera.getHeight()) + 508)); // aguja
            }
            break;
    }
    
    if(game.gameStatus != partidaSlot::FINISHED || whoWins != 2){
        
        // semaforo, es autonomo si esta funcionando se ve
        semaforo.draw(ptMarcadorUno.x,ptMarcadorUno.y); // semaforo en la misma pos que la esfera
    
        playerTwo.drawConnection(); // barra de calidad de conexion
        mascaraBarra.draw(0, 0);
    }
    
    secondWindow.end();
}


//--------------------------------------------------------------
void ofApp::finishedSemaforo(){
    // se acabo la cuenta atras asi que zapatilla
    game.racing();
    semaforo.stop();
}
//--------------------------------------------------------------
void ofApp::loadedSemaforo(){
    // el semaforo esta visible
    game.countdown();
}


//--------------------------------------------------------------
void ofApp::playerOneWins(){
    // el player uno acaba de completar la 10 vuelta
    game.finished();
    whoWins = 1;
}
//--------------------------------------------------------------
void ofApp::playerTwoWins(){
    // el player uno acaba de completar la 10 vuelta
    game.finished();
    whoWins = 2;
}
//--------------------------------------------------------------
void ofApp::playerOneNewLap(){
    // vuelta nueva coche 1
    playerOne.pasoPorVuelta();
}

//--------------------------------------------------------------
void ofApp::playerTwoNewLap(){
    // vuelta nueva coche 2
    playerTwo.pasoPorVuelta();
}


// --------------------------------------------------------------- //
// --------------------------------------------------------------- //
// --------------------------------------------------------------- //
// --------------------------------------------------------------- //
// ---------------------- CONTROL DE JUEGO ----------------------- //
// --------------------------------------------------------------- //
// --------------------------------------------------------------- //
// --------------------------------------------------------------- //
// --------------------------------------------------------------- //
void ofApp::nuevaPartida(){
    // aqui le explica la azafata a los users como va lo del mindwave, el blink y todo eso
    // esta aqui hasta que todos tienen wai la conexion y estan listos
    // no suena ni se mueve
    // solo se ve el dashboard
     whoWins = 0;
    
    playerOne.resetLapCounter();
    playerTwo.resetLapCounter();
    
    game.readyToRun();
    
}
//--------------------------------------------------------------
void ofApp::encederMotoresPartida(){
    // ahora con todos con se–al wai encendemos el sonido para que oigan el brum brum
    // los coches aun no se mueven
    game.startEngines();
}
//--------------------------------------------------------------
void ofApp::empezarPartida(){
    // lanza el semaforo que al terminar comienza la partida
    semaforo.go();
}

// --------------------------------------------------------------- //
// --------------------------------------------------------------- //





//--------------------------------------------------------------
void ofApp::guardaGui(){
    // pasamos las posiciones al game
    game.ptoServoPlayerOne.set(playerOne.servoMin, playerOne.servoMax);
    game.ptoServoPlayerOne.set(playerTwo.servoMin, playerTwo.servoMax);
    
    playerOne.useAttention = useAttention;
    playerOne.useMeditation = useMeditation;
    playerOne.useBooth = useBooth;
    
    playerTwo.useAttention = useAttention;
    playerTwo.useMeditation = useMeditation;
    playerTwo.useBooth = useBooth;
}



//--------------------------------------------------------------
void ofApp::exit(){
    game.cierra();
    playerOne.closeMindWave();
    
    ofRemoveListener(playerOne.playerWin, this, &ofApp::playerOneWins);
    ofRemoveListener(playerTwo.playerWin, this, &ofApp::playerTwoWins);
    ofRemoveListener(game.pasoPorVueltaOne, this, &ofApp::playerOneNewLap);
    ofRemoveListener(game.pasoPorVueltaTwo, this, &ofApp::playerTwoNewLap);
    ofRemoveListener(gui.savePressedE, this, &ofApp::guardaGui);
    ofRemoveListener(semaforo.terminado, this, &ofApp::finishedSemaforo);
    ofRemoveListener(semaforo.cargado, this, &ofApp::loadedSemaforo);
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'd') showGui = !showGui;
    
    if(key == 'c') semaforo.go();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}


