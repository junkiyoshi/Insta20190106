#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(239);

	ofNoFill();
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	float radius = 250;

	ofNoFill();
	for (int i = 0; i < 150; i++) {

		vector<glm::vec3> vertices;
		float noise_seed_x = ofRandom(1000);
		float noise_seed_y = ofRandom(1000);
		float noise_seed_z = ofRandom(1000);
		for (int len = 0; len < 30; len++) {

			float x = ofMap(ofNoise(noise_seed_x, (ofGetFrameNum() + len) * 0.005), 0, 1, -ofGetWidth() * 0.5, ofGetHeight() * 0.5);
			float y = ofMap(ofNoise(noise_seed_y, (ofGetFrameNum() + len) * 0.005), 0, 1, -ofGetHeight() * 0.5, ofGetHeight() * 0.5);
			float z = ofMap(ofNoise(noise_seed_z, (ofGetFrameNum() + len) * 0.005), 0, 1, -ofGetWidth() * 0.5, ofGetHeight() * 0.5);

			glm::vec3 point = glm::vec3(x, y, z);
			if (glm::length(point) < radius) {

				point = glm::normalize(point) * (radius + 1);
			}

			vertices.push_back(point);
		}

		ofBeginShape();
		ofSetColor(239, ofMap(glm::length(vertices.back()), radius, radius + 100, 255, 0));
		ofVertices(vertices);
		ofEndShape();

		ofDrawSphere(vertices.back(), 3);
	}
	
	ofFill();
	ofSetColor(39);
	ofDrawSphere(glm::vec3(), radius);

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}