import re 
import string 
import os.path
from os import path

def CountAll():
	#Open the file in read mode
	text = open("CS210_Project_Three_Input_File.txt", "r")

	#Create the empty disctionary to store the found words
	dictionary = dict()

	#Check each line of the input file 
	for line in text:
		#remove the spaces and newline chars
		line = line.strip()
		#Convert words to lower case
		word = line.lower()
		#check if the word is in the dict
		if word in dictionary:
			dictionary[word] = dictionary[word] + 1
		else:
			#if word is not in the dictionary, add it with a value of 1 
			dictionary[word] = 1

	#Print all contents of the dictionary
	for key in list (dictionary.keys()):
		print(key.capitalize(), ":", dictionary[key])

	#Close the open file 
	text.close()

def CountInstances(searchTerm):
	#Convert the user input to lowercase 
	searchTerm = searchTerm.lower()

	#Open the file in read mode
	text = open("CS210_Project_Three_Input_File.txt", "r")

	#Create variable to track how many times the search term was "found"
	wordCount = 0

	#Check each line of the file
	for line in text:
		line = line.strip()
		word = line.lower()
		#Check if the found word is equal to the user input
		if word == searchTerm:
			wordCount += 1
	#Return the number of times the search term was found
	return wordCount

	#Close the file
	text.close()

def CollectData():
	#Open the file in read mode
	text = open("CS210_Project_Three_Input_File.txt", "r")

	#Create and/or write the file frequency.dat
	frequency = open("frequency.dat", "w")

	#Create an empty dictionary to store the found words
	dictionary = dict()

	for line in text:
		line = line.strip()
		word = line.lower()

		#Check if the word is already in the dictionary
		if word in dictionary:
			dictionary[word] = dictionary[word] + 1
		else:
			dictionary[word] = 1

	#Write each key and value pair in dictionary to frequency.dat
	for key in list(dictionary.keys()):
		#Format the key-value pair as strings 
		frequency.write(str(key.capitalize()) + " " + str(dictionary[key]) + "\n")

	#Close the opened files
	text.close()
	frequency.close()