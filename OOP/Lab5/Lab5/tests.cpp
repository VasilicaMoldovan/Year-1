#include "tests.h"
#include <assert.h>
#include <iostream>

void Tests::TestDomain() {
	std::string title, type, date, mirrorImage;
	int numberOfRepetitions;
	title = "cleanup";
	type = "merchant room clean spill";
	date = "01-13-1248";
	mirrorImage = "sparkling room";
	numberOfRepetitions = 5;
	Refurbishment newTask = Refurbishment(title, type, date, numberOfRepetitions, mirrorImage);
	assert(newTask.getNumberOfRepetitions() == numberOfRepetitions);
	assert(newTask.getDate() == "01-13-1248");
	assert(newTask.getMirrorImage() == "sparkling room");
	assert(newTask.getTitle() == "cleanup");
	assert(newTask.getType() == "merchant room clean spill");
	newTask.setDate("12-10-1279");
	newTask.setMirrorImage("a perfect room");
	newTask.setNumberOfRepetitions(18);
	newTask.setTitle("garden");
	newTask.setType("the most marvellous garden ever");
	assert(newTask.getNumberOfRepetitions() == 18);
	assert(newTask.getDate() == "12-10-1279");
	assert(newTask.getMirrorImage() == "a perfect room");
	assert(newTask.getTitle() == "garden");
	assert(newTask.getType() == "the most marvellous garden ever");

	std::string newString;
	newString = "Title: garden, Type: the most marvellous garden ever, Date: 12-10-1279, Number of repetitions: 18, Mirror Image: a perfect room";
	assert(newString == newTask.toString());
}

void Tests::TestController() {
	Refurbishment newElem{};
	TaskControllerModeA newController;
	newController.readRepositoryFromFile("inputTest.txt");
	assert(newController.getNumberOfRefurbishments() == 6);
	std::string title, type, date, mirrorImage;
	int numberOfRepetitions;
	title = "cleanup";
	type = "more cleanup";
	date = "01-13-1200";
	mirrorImage = "a perfect room";
	numberOfRepetitions = 29;
	Refurbishment newTask = Refurbishment(title, type, date, numberOfRepetitions, mirrorImage);
	newController.addNewRefurbishment(newTask);
	//assert(newController.existingTask(newTask) == true);
	assert(newController.getNumberOfRefurbishments() == 7);
	int count = 0;
	for (auto element : newController.getAllRefurbishments()) {
		if (element.getTitle() == newTask.getTitle()) {
			count += 1;
			break;
		}
	}
	assert(count == 1);
	newController.deleteRefurbishment(newTask);
	assert(newController.getNumberOfRefurbishments() == 6);
	title = "cleanup";
	type = "more cleanup";
	date = "01-13-1200";
	mirrorImage = "a perfect room";
	numberOfRepetitions = 29;
	Refurbishment secondTask = Refurbishment(title, type, date, numberOfRepetitions, mirrorImage);
	newController.updateExistingRefurbishment(secondTask);
	newController.writeRepoToFile();
	count = 0;
	for (auto element : newController.getAllRefurbishments()) {
		if (element.getTitle() == newTask.getTitle()) {
			count += 1;
			assert(element.getType() == "more cleanup");
			assert(element.getDate() == "01-13-1200");
			assert(element.getMirrorImage() == "a perfect room");
			assert(element.getNumberOfRepetitions() == 29);
			break;
		}
	}
	Refurbishment currentChore = newController.seeNextChore(0);
	for (auto element : newController.getAllRefurbishments()) {
		assert(element.getTitle() == currentChore.getTitle());
		assert(element.getType() == currentChore.getType());
		assert(element.getMirrorImage() == currentChore.getMirrorImage());
		break;}
	newController.saveCurrentChore("cleanup");
	std::vector<Refurbishment> savedChores = newController.getAllSavedChores(count);
	assert(count == 1);
	assert(savedChores.size() == 1);
	std::vector<Refurbishment>  filteredChores = newController.listAllChoresOfTypeAndProperty("pam", 50, count);
	assert(filteredChores.size() == 2);
	for (auto element : filteredChores) {
		assert(element.getNumberOfRepetitions() < 50);
	}
}

void Tests::TestControllerLab9() {
	TaskRepository *baseRepository = new TestRepository();
	TaskRepository *fileRepository = new TestRepository();
	RepositoryValidator *repoValidator = new FakeValidator();
	TaskControllerModeA testController(baseRepository, fileRepository, repoValidator);

	Refurbishment newTask = {"cleanup", "merchant room clean spill", "01-11-1248", 5, "sparkling room"};

	Refurbishment anotherTask = { "title", "biggest room clean spill", "17-11-1148", 18, "perfection" };
	try {
		testController.addNewRefurbishment(newTask);
		assert(false);
	}
	catch (RefurbishmentException& exception) {
		assert(true);
	}
	assert(testController.addNewRefurbishment(anotherTask) == false);

	Refurbishment secondTask = { "title", "biggest room clean spill", "17-10-1148", 18, "perfection"};
	assert(testController.deleteRefurbishment(newTask) == true);
	assert(testController.deleteRefurbishment(secondTask) == true);

	delete baseRepository;
	delete fileRepository;
}
