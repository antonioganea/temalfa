// Antonio-Alexandru Ganea // Grupa 135 // Tema LFA - Cazul c) // Automat determinist/nedeterminist

#include <stdio.h>
#include <vector>
#include <map>
#include <string.h>

FILE * fin;

struct Node{
    std::map< char, std::vector<int> > m;
    bool finalState;
    Node(){
        finalState = false;
    }
};

bool vectorContains( std::vector<int> myvec, int number ){
    for (std::vector<int>::iterator it = myvec.begin() ; it != myvec.end(); ++it){
        if ( *it == number ){
            return true;
        }
    }
    return false;
}

void printVector( std::vector<int> myvec ){
    for (std::vector<int>::iterator it = myvec.begin() ; it != myvec.end(); ++it)
        printf("%d ",*it);
    puts("");
}

bool checkIfStatesContainFinishingState( Node nodes[], std::vector<int> myvec ){
    for (std::vector<int>::iterator it = myvec.begin() ; it != myvec.end(); ++it) {
        if ( nodes[*it].finalState ) {
            return true;
        }
    }
    return false;
}


int main(){
    fin = fopen( "input_nedeterminist.txt", "r" );

    int states, transitions;
    fscanf(fin,"%d%d",&states,&transitions);

    Node nodes[states+1];

    for ( int i = 0; i < transitions; i++ ){
        int a,b;
        char temp[100];
        fscanf(fin,"%d%d%s",&a,&b,&temp);
        char c = temp[0];

        // din a in b prin c
        nodes[a].m[c].push_back(b);
    }

    int initialState;

    fscanf(fin,"%d",&initialState);

    int finalStates;

    fscanf(fin,"%d", &finalStates);

    for ( int i = 0; i < finalStates; i++ ){
        int temp;
        fscanf(fin,"%d",&temp);
        nodes[temp].finalState = true;
    }

    int words;
    fscanf(fin,"%d",&words);

    char letters[] = "abc";


    char word[1000];
    fscanf(fin,"%s",&word);

    std::vector<int> currentStates;
    currentStates.push_back(initialState);

    std::vector<int> nextStates;

    puts("Current states:");
    printVector(currentStates);

    for ( int i = 0; i < strlen(word); i++ ){
        nextStates.clear();
        // iterate through current states
        for (std::vector<int>::iterator it = currentStates.begin() ; it != currentStates.end(); ++it){
            // iterate through current state next states on every possible character
            for ( int C = 0; C < strlen(letters); C++ ) {
                for( std::vector<int>::iterator it2 = nodes[*it].m[letters[C]].begin(); it2 != nodes[*it].m[letters[C]].end(); ++it2 ){
                    printf("Jump %d -> %d by %c\n", *it, *it2, letters[C]);
                    if ( ! vectorContains(nextStates, *it2) ){
                        nextStates.push_back(*it2);
                    }
                }
            }
        }
        currentStates.clear();
        currentStates.assign(nextStates.begin(), nextStates.end());

        puts("Current states:");
        printVector(currentStates);
    }

    if ( checkIfStatesContainFinishingState( nodes, currentStates ) ) {
        printf("Cuvantul '%s' este acceptat!\n", word);
    } else {
        printf("Cuvantul '%s' NU este acceptat!\n", word);
    }
    return 0;
}
