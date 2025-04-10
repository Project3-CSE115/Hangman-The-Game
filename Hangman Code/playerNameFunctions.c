bool nameTaken(char playerName[MAX_LENGTH]) {
    char name[MAX_LENGTH];

    FILE *file = fopen("players.txt","r");
    while (fscanf(file, "%s", name) != EOF) {
        if (strcmp(playerName,name) == 0) {
            return true;
        }
    }
    fclose(file);
    return false;
}

bool nameValid(char playerName[MAX_LENGTH]) {
    
    if (strlen(playerName) > 20) {
        return false;
    } else {
        return true;
    }
}
