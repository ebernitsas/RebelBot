#include "ofApp.h"



string codes[36] = {"01", "1000", "1010", "100", "0", "0010", "110", "0000",
                    "00", "0111", "101", "0100", "11", "10", "111", "0110",
                    "1101", "010", "000", "1", "001", "0001", "011", "1001",
                    "1011", "1100",
                    "01111", "00111", "00011", "00001", "00000",
                    "10000", "11000", "11100", "11110", "11111"};

char letters[36] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
                    'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                    'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7',
                    '8', '9', '0'};

string msg; //establish message
string reversemsg;
int unit = 10;
int xStart = 50;
int yStart = 300;





//--------------------------------------------------------------
void ofApp::setup(){
    
    //------------Serial Setup-------------//
	ofSetVerticalSync(true);
	
	bSendSerialMessage = false;
	ofBackground(255);	
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	font.load("DIN.otf", 14);
	
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
	int baud = 9600;
	//serial.setup(0, baud); //open the first device
	//serial.setup("COM4", baud); // windows example
	serial.setup("/dev/tty.usbmodem1411", baud); // mac osx example
	//serial.setup("/dev/ttyUSB0", baud); //linux example
    
    //------------------------------------//
    
    
    ofSetColor(100,0,0);
    
    
    
	
}

//--------------------------------------------------------------
void ofApp::update(){

    
        
        
    
		
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    int x = xStart;
    int y = yStart;
    
    int offset = 0;
    
    
    
	//msg += "";
	//msg += "nBytes read " + ofToString(nBytesRead) + "\n";
	font.drawString(msg, 50, 200);
    
    for (int i = 0; i < msg.length(); i++){
        offset++;
        for (int j = 0; j <=36; j++){
            if (letters[j] == msg[i]){
                if ((x + unit*i + offset*unit +
                     unit*codes[j].length()*2) > ofGetWindowWidth() - 100){
                    x = 0;
                    y += 100;
                    offset = 0;
                }
                for (int k = 0; k < codes[j].length(); k++){
                    if (codes[j][k] == '0'){
                        offset++;
                        ofDrawCircle(x + unit*i + offset*unit , y, unit/2);
                        offset++;
                    }
                    else {
                        offset++;
                        ofDrawRectangle(x + unit*i + offset*unit, y-unit/2, unit*3, unit);
                        offset += 3;
                    }
                    
                    
                }
            }
        }
            
        if (msg[i] == ' '){
            offset += 3;
            //cout << "space" << endl;
        }
        
        
    }
    
    
    
    
    
    
    
        
}
//--------------------------------------------------------------

string ofxGetSerialString(ofSerial &serial, char until) {
    static string str;
    stringstream ss;
    char ch;
    int ttl=1000;
    while ((ch=serial.readByte())>0 && ttl-->0 && ch!=until) {
        ss << ch;
    }
    str+=ss.str();
    if (ch==until) {
        string tmp=str;
        str="";
        return tmp;
    } else {
        return "";
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    
    if (isalpha(key) || isdigit(key) || (key ==S ' ')){
        ofSetColor(100,0,0);
        msg += key;
        
        
    }
    
    else if (key == 127){ //delete button
        msg.pop_back();
    }
    
    else if (key == 13) { //enter
        int len = msg.length() - 1;
        for(int i = 0; i <= len; i++){
            reversemsg += msg[len - i];
        }
        writingSerial(serial);
        ofSetColor(0,0,200);
        cout << "enter" << " " << reversemsg << endl;
        
        
    }

    
    else if (key == 61){            //plus sign
        //writingSerial(serial);
        string x = ofxGetSerialString(serial, '@');
        
        cout << x << endl;
        
    }
    
    
    cout << key << endl;
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

   
}

//--------------------------------------------------------------
void ofApp::writingSerial(ofSerial &serial){
    
    //0 = dot
    //1 = line
    //2 = letter over
    //3 = word space
    
    cout << reversemsg << " message" << reversemsg.length() << endl;
    for (int i = 0; i < reversemsg.length(); i++){
        switch(reversemsg[i]){
            case('a'):
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('b'):
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('c'):
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('d'):
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('e'):
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('f'):
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('g'):
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('h'):
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('i'):
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('j'):
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('k'):
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('l'):
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('m'):
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('n'):
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('o'):
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('p'):
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('q'):
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('r'):
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('s'):
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('t'):
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('u'):
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('v'):
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('w'):
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('x'):
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('y'):
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('z'):
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('0'):
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('1'):
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('2'):
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('3'):
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('4'):
                serial.writeByte('1');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('5'):
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('2');
                break;
            case('6'):
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('7'):
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('8'):
                serial.writeByte('0');
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case('9'):
                serial.writeByte('0');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('1');
                serial.writeByte('2');
                break;
            case(' '):
                serial.writeByte('3');
                break;

        }
        serial.writeByte('#');
        serial.writeByte('%'); //signify end
    }

    
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    


    
	
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}

