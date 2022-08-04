#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofSetColor(0);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	vector<glm::vec2> location_list;
	for (int i = 0; i < 80; i++) {

		auto location = glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0015), 0, 1, -500, 500), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0015), 0, 1, -500, 500));
		location_list.push_back(location);
	}

	for (int i = 0; i < location_list.size(); i++) {

		ofFill();
		ofDrawCircle(location_list[i], 8);
		for (int k = i + 1; k < location_list.size(); k++) {

			auto distance = glm::distance(location_list[i], location_list[k]);
			if (distance < 100) {

				auto center = location_list[i] + ((location_list[k] - location_list[i]) / 2);
				auto i_center = location_list[i] + ((location_list[k] - location_list[i]) / 2) * (distance - 12) / distance;
				auto k_center = location_list[k] + ((location_list[i] - location_list[k]) / 2) * (distance - 12) / distance;;

				ofDrawLine(location_list[i], i_center);

				auto rad_start = std::atan2(location_list[i].y - location_list[k].y, location_list[i].x - location_list[k].x) - PI * 0.5;

				ofNoFill();
				ofBeginShape();
				for (auto rad = rad_start; rad < rad_start + PI; rad += PI / 180) {

					ofVertex(center + glm::vec2(6 * cos(rad), 6 * sin(rad)));
				}
				ofEndShape();

				ofDrawLine(location_list[k], k_center);

				rad_start = std::atan2(location_list[k].y - location_list[i].y, location_list[k].x - location_list[i].x) - PI * 0.5;

				ofNoFill();
				ofBeginShape();
				for (auto rad = rad_start; rad < rad_start + PI; rad += PI / 180) {

					ofVertex(center + glm::vec2(6 * cos(rad), 6 * sin(rad)));
				}
				ofEndShape();
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}