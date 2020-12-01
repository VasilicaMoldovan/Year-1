#include <stdio.h>
#include <stdlib.h>
#include "Repository.h"

int existingSubstance(TElem* substance, SubstanceRepository *repositoryList) {
	for (int index = 0; index < repositoryList->lengthOfVector; index++) {
		if (equalSubstances(substance, repositoryList->vectorOfSubstances[index]))
			return index;
	}
	return -1;
}

void addSubstance(TElem* substance, char** errorString, SubstanceRepository *repositoryList) {
	if (existingSubstance(substance, repositoryList) != -1)
		strcpy(errorString, "This substance already exists in the apothecary!\n");
	else {
		if (repositoryList->lengthOfVector == repositoryList->capacityOfVector) {
			repositoryList->capacityOfVector *= 1.5;
			repositoryList->vectorOfSubstances = (TElem **)realloc(repositoryList->vectorOfSubstances, sizeof(TElem *) *repositoryList->capacityOfVector);
		}
		else {
			repositoryList->vectorOfSubstances[repositoryList->lengthOfVector] = substance;
			repositoryList->lengthOfVector += 1;
		}
	}
}

void updateSubstance(TElem* substance, char** errorString, SubstanceRepository *repositoryList) {
	int indexOfSubstance = existingSubstance(substance, repositoryList);
	if (indexOfSubstance == -1)
		strcpy(errorString, "The required substance does not exist!\n");
	else {
		repositoryList->vectorOfSubstances[indexOfSubstance]->catalogingNumber = substance->catalogingNumber;
		repositoryList->vectorOfSubstances[indexOfSubstance]->intendedUse = substance->intendedUse;
		repositoryList->vectorOfSubstances[indexOfSubstance]->state = substance->state;
		repositoryList->vectorOfSubstances[indexOfSubstance]->potency = substance->potency;
	}
}

void deleteSubstance(TElem* substance, char** errorString, SubstanceRepository *repositoryList) {
	int indexOfSubstance = existingSubstance(substance, repositoryList);
	if (indexOfSubstance == -1)
		strcpy(errorString, "The required substance does not exist!\n");
	else {
		for (int newIndex = indexOfSubstance; newIndex < repositoryList->lengthOfVector - 1; newIndex++)
			repositoryList->vectorOfSubstances[newIndex] = repositoryList->vectorOfSubstances[newIndex + 1];
		repositoryList->lengthOfVector--;
	}
}

void listSubstances(char** stringToBePrinted, SubstanceRepository *repositoryList) {
	char buffer[15];
	strcpy(stringToBePrinted, "");
	for (int index = 0; index < repositoryList->lengthOfVector; index++) {
		strcat(stringToBePrinted, "Cataloging Number: ");
		_itoa(repositoryList->vectorOfSubstances[index]->catalogingNumber, buffer, 10);
		strcat(stringToBePrinted, buffer);
		strcat(stringToBePrinted, " State: ");
		strcat(stringToBePrinted, repositoryList->vectorOfSubstances[index]->state);
		strcat(stringToBePrinted, ", Intended Use: ");
		strcat(stringToBePrinted, repositoryList->vectorOfSubstances[index]->intendedUse);
		strcat(stringToBePrinted, ", Potency: ");
		_itoa(repositoryList->vectorOfSubstances[index]->potency, buffer, 10);
		strcat(stringToBePrinted, buffer);
		strcat(stringToBePrinted, "\n");
	}
}

void listIntendedUseSubstances(char** stringToBePrinted, char* intendedUse, SubstanceRepository *repositoryList) {
	char buffer[15];
	strcpy(stringToBePrinted, "");
	for (int index = 0; index < repositoryList->lengthOfVector; index++) {
		if (strstr(repositoryList->vectorOfSubstances[index]->intendedUse, intendedUse) != NULL) {
			strcat(stringToBePrinted, "Cataloging Number: ");
			_itoa(repositoryList->vectorOfSubstances[index]->catalogingNumber, buffer, 10);
			strcat(stringToBePrinted, buffer);
			strcat(stringToBePrinted, " State: ");
			strcat(stringToBePrinted, repositoryList->vectorOfSubstances[index]->state);
			strcat(stringToBePrinted, ", Intended Use: ");
			strcat(stringToBePrinted, repositoryList->vectorOfSubstances[index]->intendedUse);
			strcat(stringToBePrinted, ", Potency: ");
			_itoa(repositoryList->vectorOfSubstances[index]->potency, buffer, 10);
			strcat(stringToBePrinted, buffer);
			strcat(stringToBePrinted, "\n");
		}
	}
}

void deallocateRepository(SubstanceRepository *repositoryList) {
	for (int index = 0; index < repositoryList->lengthOfVector; index++) {
		delete(repositoryList->vectorOfSubstances[index]);
	}
	free(repositoryList->vectorOfSubstances);
	free(repositoryList);
}

SubstanceRepository* createRepo() {
	SubstanceRepository* repositoryList = (SubstanceRepository*)malloc(sizeof(SubstanceRepository));
	repositoryList->lengthOfVector = 0;
	repositoryList->capacityOfVector = 200;
	repositoryList->vectorOfSubstances = (TElem**)malloc(repositoryList->capacityOfVector * sizeof(TElem*));

	return repositoryList;
}


int comparePotencyValues(TElem* firstSubstance, TElem* secondSubstance) {
	if (firstSubstance->potency <= secondSubstance->potency)
		return 1;
	return 0;
}

int compareDescendingPotencyValues(TElem* firstSubstance, TElem* secondSubstance) {
	if (firstSubstance->potency >= secondSubstance->potency)
		return 1;
	return 0;
}


void sortMaximumPotencyValue(char** stringToBePrinted, int maximumPotencyValue, SubstanceRepository *repositoryList, int(*Relation)(TElem* firstSubstance, TElem* secondSubstance)) {
	TElem **listOfSubstances;
	int lengthOfListOfSubstances = 0;
	listOfSubstances = (TElem**)malloc(repositoryList->capacityOfVector * sizeof(TElem*));
	for (int index = 0; index < repositoryList->lengthOfVector; index++) {
		if (repositoryList->vectorOfSubstances[index]->potency < maximumPotencyValue) {
			listOfSubstances[lengthOfListOfSubstances] = repositoryList->vectorOfSubstances[index];
			lengthOfListOfSubstances++;
		}
	}
	TElem *aux;
	for (int index1 = 0; index1 < lengthOfListOfSubstances - 1; index1++) {
		for (int index2 = index1 + 1; index2 < lengthOfListOfSubstances; index2++) {
			if (!Relation(listOfSubstances[index1], listOfSubstances[index2])) {
				aux = listOfSubstances[index1];
				listOfSubstances[index1] = listOfSubstances[index2];
				listOfSubstances[index2] = aux;
			}
		}
	}

	listMaximumPotencyValue(stringToBePrinted, listOfSubstances, lengthOfListOfSubstances);
}


void listMaximumPotencyValue(char** stringToBePrinted, TElem **vectorOfSubstances, int lengthOfVectorOfSubstances) {
	char buffer[15];
	strcpy(stringToBePrinted, "");
	for (int index = 0; index < lengthOfVectorOfSubstances; index++) {
		strcat(stringToBePrinted, "Cataloging Number: ");
		_itoa(vectorOfSubstances[index]->catalogingNumber, buffer, 10);
		strcat(stringToBePrinted, buffer);
		strcat(stringToBePrinted, " State: ");
		strcat(stringToBePrinted, vectorOfSubstances[index]->state);
		strcat(stringToBePrinted, ", Intended Use: ");
		strcat(stringToBePrinted, vectorOfSubstances[index]->intendedUse);
		strcat(stringToBePrinted, ", Potency: ");
		_itoa(vectorOfSubstances[index]->potency, buffer, 10);
		strcat(stringToBePrinted, buffer);
		strcat(stringToBePrinted, "\n");
	}
}

void searchSubstance(TElem* substance, int catalogingNumber, SubstanceRepository *repositoryList) {
	for (int index = 0; index < repositoryList->lengthOfVector; index++) {
		if (repositoryList->vectorOfSubstances[index]->catalogingNumber == catalogingNumber) {
			substance->catalogingNumber = catalogingNumber;
			substance->potency = repositoryList->vectorOfSubstances[index]->potency;
			strcpy(substance->state, repositoryList->vectorOfSubstances[index]->state);
			strcpy(substance->intendedUse, repositoryList->vectorOfSubstances[index]->intendedUse);
			break;
		}
	}
}


int filterByIntendedUse(Substance* newSubstance, char* intendedUse) {
	if (strstr(newSubstance->intendedUse, intendedUse) != NULL)
		return 1;
	return 0;
}

int filterByState(Substance* newSubstance, char* state) {
	if (strstr(newSubstance->state, state) != NULL)
		return 1;
	return 0;
}

void filerByProperty(char** stringToBePrinted, char* property, SubstanceRepository *repositoryList, int(*Relation)(TElem* substance, char* newProperty)) {
	char buffer[15];
	strcpy(stringToBePrinted, "");
	for (int index = 0; index < repositoryList->lengthOfVector; index++) {
		if (Relation(repositoryList->vectorOfSubstances[index], property)) {
			strcat(stringToBePrinted, "Cataloging Number: ");
			_itoa(repositoryList->vectorOfSubstances[index]->catalogingNumber, buffer, 10);
			strcat(stringToBePrinted, buffer);
			strcat(stringToBePrinted, " State: ");
			strcat(stringToBePrinted, repositoryList->vectorOfSubstances[index]->state);
			strcat(stringToBePrinted, ", Intended Use: ");
			strcat(stringToBePrinted, repositoryList->vectorOfSubstances[index]->intendedUse);
			strcat(stringToBePrinted, ", Potency: ");
			_itoa(repositoryList->vectorOfSubstances[index]->potency, buffer, 10);
			strcat(stringToBePrinted, buffer);
			strcat(stringToBePrinted, "\n");
		}
	}
}