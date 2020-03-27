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
    void printLinks(char stuff){
        for (std::vector<int>::iterator it = m[stuff].begin() ; it != m[stuff].end(); ++it)
            printf("=%d    ",*it);
        puts("");
            //std::cout << ' ' << *it;
    }
};

char word[] = "abcaa";

void printAccepted( int pos ){
    for ( int i = 0; i < pos; i++ ){
        printf("%c",word[i]);
    }
    puts("");
}

void launch( Node nodes[], int currentNode, int windex ){

    //printf("Current node : %d\n",currentNode);

    if ( nodes[currentNode].finalState == true ){
        //printf("Accepted : state %d - windex %d\n",currentNode,windex);
        printAccepted(windex);
    }

    //printf("Current litera : %s\n",currentChar);
    std::vector<int> * myvec = &(nodes[currentNode].m[word[windex]]);

    for (std::vector<int>::iterator it = myvec->begin() ; it != myvec->end(); ++it){
        //printf("=%d    ",*it);

        //if ( word[windex+1] != '\0' ){
            launch(nodes,*it,windex+1);
        //}
    }

}

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


int main(){

    fin = fopen( "input_nedeterminist.txt", "r" );

    int states, transitions;

    fscanf(fin,"%d%d",&states,&transitions);
    printf("%d %d\n\n",states,transitions);

    Node nodes[states+1];

    for ( int i = 0; i < transitions; i++ ){
        int a,b;
        char temp[100];
        fscanf(fin,"%d%d%s",&a,&b,&temp);
        char c = temp[0];

        // din a in b prin c
        nodes[a].m[c].push_back(b);
        printf("%d %d %c\n",a,b,c);
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

    //puts("Accepted values:");
    //launch( nodes, initialState, 0);

    std::vector<int> currentStates;
    currentStates.push_back(initialState);

    std::vector<int> nextStates;

    puts("Current states:");
    printVector(currentStates);

    for ( int i = 0; i < strlen(word); i++ ){//strlen(word)
        //printf("%c",word[i]);

        nextStates.clear();
        // iterate through current states
        for (std::vector<int>::iterator it = currentStates.begin() ; it != currentStates.end(); ++it){
            //printf("=%d\n",*it);

            // iterate through current state next states on current character
            for( std::vector<int>::iterator it2 = nodes[*it].m[word[i]].begin(); it2 != nodes[*it].m[word[i]].end(); ++it2 ){
                //printf("%d ",*it2);

                if ( ! vectorContains(nextStates, *it2) ){
                    nextStates.push_back(*it2);
                }

            }
        }
        currentStates.clear();
        currentStates.assign(nextStates.begin(), nextStates.end());

        puts("Current states:");
        printVector(currentStates);
    }

    return 0;
}
