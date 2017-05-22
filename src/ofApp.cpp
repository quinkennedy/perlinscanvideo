#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
#ifdef TARGET_OPENGLES
    shader.load("shadersES2/shader");
#else
    if(ofIsGLProgrammableRenderer()){
        shader.load("shadersGL3/shader");
    }else{
        shader.load("shadersGL2/shader");
    }
#endif
    
    video.load("movies/alex_slow.mov");
    video.play();
    prevVideoFrame = -1;
    
    ofImage distortionMap;
    distortionMap.loadImage("distortion.png");
    
    maskFbo.allocate(video.getWidth(), video.getHeight());
    
    scan.setup(video.getWidth(), video.getHeight(), 120, OF_IMAGE_COLOR);
    scan.setDelayMap(distortionMap);
    //blending means the edges between the scans are feathered
    scan.setBlending(true);
}

bool ofApp::isFrameNew(){
    return (   (prevVideoFrame == -1
                && video.getCurrentFrame() >= 0)
            || (prevVideoFrame >= 0
                && video.getCurrentFrame() != prevVideoFrame));
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    if (isFrameNew()){
        scan.addImage(video.getPixels());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    maskFbo.begin();
    shader.begin();
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform2f("u_resolution", maskFbo.getWidth(), maskFbo.getHeight());
    ofRect(0, 0, maskFbo.getWidth(), maskFbo.getHeight());
    shader.end();
    maskFbo.end();
    
    ofPixels pix;
    maskFbo.readToPixels(pix);
    scan.setDelayMap(pix);
    
    scan.getOutputImage().draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
