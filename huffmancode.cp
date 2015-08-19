//
//  main.cpp
//  huffmancode
//
//  Created by colan connon on 4/23/15.
//  Copyright (c) 2015 colan connon. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <cstdarg>
using namespace std;


class HuffmanNode{
	/*
	Node class to represent the nodes of the binary tree to produce
	the huffmancodes
	Keeps track of the data and the frequency, as well as the left and
	right nodes.
	*/

public:
	int frequency;
	string data;
	HuffmanNode(string data, int frequency);
	HuffmanNode();
	HuffmanNode(const HuffmanNode& hNode);
	HuffmanNode *left;
	HuffmanNode *right;
};

HuffmanNode::HuffmanNode(string data, int frequency){
	//Basic constructor class
	this->data = data;
	this->frequency = frequency;
	this->left = NULL;
	this->right = NULL;
};
HuffmanNode::HuffmanNode(){

};
HuffmanNode::HuffmanNode(const HuffmanNode& hNode){
	// copy constructor
	this->data = hNode.data;
	this->frequency = hNode.frequency;
	this->left = hNode.left;
	this->right = hNode.right;

};
struct compare {
	//comparison struct required for the priority queue
	bool operator()(HuffmanNode hNode1, HuffmanNode hNode2){
		return hNode1.frequency > hNode2.frequency;
	}
};
vector<HuffmanNode> readTextFile(){
	/*
	File utility function
	Use this function to read the integers from a file
	into the vector so the algorithm can process the vector
	*/
	vector<HuffmanNode> fileInputVector;
	ifstream file;
	//open the file
	file.open("data.txt");
	string fileChar;
	int fileint;
	if (file.is_open()) {
		while (!file.eof()) {
			// Read an int and a string into variables to constructor a new
			// node to add to the node vector
			file >> fileChar;
			file >> fileint;
			HuffmanNode *node = new HuffmanNode(fileChar, fileint);
			fileInputVector.push_back(*node);
		}
		return fileInputVector;
	}
	else{
		cout << "File not opened" << endl;
	}
	file.close();
	return fileInputVector;
}

void printHuffManCode(HuffmanNode *root, string bitTracker){
	/*
		print the huffman code into the file
	*/
	

	ofstream myfile;
	//append to the file
	myfile.open("example.txt", std::ios_base::app);


	if (!root->data.empty()){
		// print out the data to the file and the bits to each line
		myfile << root->data << " " << bitTracker << endl;
		cout << root->data << " " << bitTracker << endl;
	}
	if (root->left != NULL){
		// if left append zero
		printHuffManCode(root->left, bitTracker + "0");
	}
	if (root->right != NULL){
		// if right append one
		printHuffManCode(root->right, bitTracker + "1");
	}
	myfile.close();
}
HuffmanNode huffmanCode(vector<HuffmanNode> huffmanNodeVector){
	// n the size of the huffman Node Vector
	int n = huffmanNodeVector.size();
	//make a priority queue to hold the nodes
	priority_queue<HuffmanNode, vector<HuffmanNode>, compare> pQueue;
	for (int i = 0; i < n; i++){
		pQueue.push(*new HuffmanNode(huffmanNodeVector.at(0)));
		huffmanNodeVector.erase(huffmanNodeVector.begin());
	}
	for (int i = 1; i < n ; i++){
		// n-1 pop the first two nodes off the queue and set them
		// to z's left and right node and set z's freq and push z onto the queue
		HuffmanNode *z = new HuffmanNode();
		HuffmanNode x = pQueue.top();
		pQueue.pop();
		HuffmanNode y = pQueue.top();
		pQueue.pop();
		z->left = new HuffmanNode(x);
		z->right = new HuffmanNode(y);
		z->frequency = x.frequency + y.frequency;
		pQueue.push(*z);
	
	}

	// return for processing in the print func
	return pQueue.top();
}
void truncateOutputFile(){
	/*
		Need this function to make sure that the file is blank from previous runs.
		this truncates all data in the file
	*/
	ofstream ofs;
	ofs.open("example.txt", ofstream::out | ofstream::trunc);
	ofs.close();
}

int main(int argc, const char * argv[]) {
	vector<HuffmanNode> huffmanNodes = readTextFile();

	HuffmanNode node = huffmanCode(huffmanNodes);
	truncateOutputFile();
	printHuffManCode(&node, "");

}
