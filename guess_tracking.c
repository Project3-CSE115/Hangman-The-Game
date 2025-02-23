for(int i = 0; i < word_length; i++) //controls attempts
        {
            if(word[i] == guess && !guessed[i])
            {
                guessed[i] = 1;
                found = 1;
                correct_guesses++;
            }
        }
        if(!found) //checks presence of guessed letter
        {
            tries++;
            printf("Incorrect! You have %d tries left\n",MAX_TRIES - tries);
        }
        if(correct_guesses == word_length)
        {
            printf("Congratulations.You have guessed the word:%s\n",word);
            break;
        }

    }
   if (correct_guesses != word_length)
{
    //displayHangman(tries); [insert Hangman display funtion later]
    printf("GAME OVER! The word was: %s\n", word);
}
    return 0;
}
