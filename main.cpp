#include<string>
#include<cstring>
#include<iostream>
using namespace std;
char **pattern=new char * [5]; // This is 2D Char array to save all the Patterns i have to search it
char *Text=new char [23]; //this char array i will save at them the Text that i will search in it
char char_branch[20]; // i used this char array in print the each branch of Tries
int branch=0; // will used for number of branch
int CharToInt[256];
char IntToChar[4];

int CharNum=0; // Value used to know how much char i skip ( used in the function of give id for each node )

void InitializeTables()
{
    CharToInt['A']=0;
    IntToChar[0]='A';

    CharToInt['C']=1;
    IntToChar[1]='C';

    CharToInt['G']=2;
    IntToChar[2]='G';

    CharToInt['T']=3;
    IntToChar[3]='T';
}

/////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
    Node* Child[4];
    Node* FL; // FailureLink of this Node
    int id; // read ids of reads ending at this location
    int Location; // this is the id of the node in the Trie
};

Node* root;

/////////////////////////////////////////////////////////////////////////////////////////////

Node* CreateTrieNode() // Create and Initialize Trie Node
{
    Node* node=new Node;
    int i;
    for(i=0; i<4; i++)
    {
        node->Child[i]=0;
        node->FL=NULL;
        node->id=-1;
        node->Location=0;

    }
    return node;
}

void InitializeTrie()
{
    root=CreateTrieNode();
}

void DeleteTrie(Node* node)
{
    int i;
    for(i=0; i<4; i++) if(node->Child[i]) DeleteTrie(node->Child[i]);
    delete node;
}

void DeleteTrie()
{
    DeleteTrie(root);
}

void InsertTrieRead(int* r, int n, int id,int Start) // Insert Read r with length n with its id in trie
{
    int i;
    int j;
    Node* cur_node=root;
    for(i=0,j=Start; i<n; i++)
    {
        if(!cur_node->Child[r[i]])
        {
            cur_node->Child[r[i]]=CreateTrieNode();
            cur_node->Child[r[i]]->Location=j;// here the Start value is used to know what is the id the node will have it.
                                              // here in every time i create  the Node i give it id depending in  Start value.
            CharNum++;              // number of char i take it and skip it within process of  create the id of the node
            j++;
        }
        cur_node=cur_node->Child[r[i]];
    }
    cur_node->id=id;
}

void InsertRead(char* read, int id,int n,int Start)// Insert read (with id) and its complement (with id+1)
{

    int r[n]; // Convert characters to integers
    for(int i=0; i<n; i++)
    {
        r[i]=CharToInt[(int)read[i]]; //  AGA ----> 020
    }


    InsertTrieRead(r, n, id,Start); // Insert read
}
char* GetAll_proper_suffix(int j,string s) // in this function i will find only one proper suffix for the pattern i have
{
    char *propar_suffix=new char[50];
    int Loop=0;
    if (s.length()==1)
    {
        propar_suffix="";      // That mean i have one character so there is no proper suffix for this pattern
        return propar_suffix;
    }
    for(int i=j; i<s.length(); i++)
    {
        propar_suffix[Loop]=s[i];
        Loop++;
    }
    propar_suffix[Loop]='\0';
    return propar_suffix;
}
Node * QueryTrieRead(int* r, int n) // Find Read r & it's node  with length n in the trie nodes
{
	int i;
    Node * ret_node;
	Node* cur_node=root;
	for(i=0;i<n;i++)
	{
		if(!cur_node->Child[r[i]])
        {
            ret_node=root;
            return ret_node;
        }
		else
        {
            ret_node=cur_node->Child[r[i]];
            cur_node=cur_node->Child[r[i]];

		}
	}
	return ret_node;
}
Node *Search_In_Trie(char *propar) // in this function i will search at proper in the Trie and find the location of this node
{
    if (strlen(propar)==0)
    {
        return root;
    }
    int r[strlen(propar)], i, n=0;
    for(i=0; propar[i]; i++)
    {
        r[i]=CharToInt[propar[i]];
        n++;
    }
    QueryTrieRead(r,n);
}
void Creat_FL(Node* curr,string curr_string ) // in this function i will find the FailuerLink for each node in the trie
{
    string real;  // it is used to save the char of father node before go in recursion of childs of this node
    int z=0;
    char *propar=new char[50]; // i will save her the proper suffix of the pattern
    if (curr_string=="")
    {
        curr->FL=NULL; //That mean no i have the root node


    }
    for(int i=0; i<4; i++)
    {
        real=curr_string;

        if(curr->Child[i])  // That mean the done have child with this char
        {
            curr_string+=IntToChar[i]; // i add this char to before char
            //cout<<"Current Node : "<<curr_string<<" location of this Node is : = "<<curr->Child[i]<<endl;

            if(curr_string.length()==1) // that mean i have node with 1 char so the FailuerLink foe this node is the root
            {
                propar=GetAll_proper_suffix(1,curr_string);
               // cout<<"Proper Suffix is "<<propar<<endl;
                curr->Child[i]->FL=root;
                //cout<<"This Node FL is Reefer to Root location :  "<<curr->Child[i]->FL<<endl;
            }
            else
            {
                for (int j=1; j<=curr_string.length(); j++) // here i will start get the all proper suffix of the node
                {                                           // then start search in trie to find the location of the node has match with this propers and make the FailuerLink of the node is this node that has matched with one of propers
                    if(z!=0) break;                         // if there is no node have matched with the propers then FailuerLink of this node is the root
                    propar=GetAll_proper_suffix(j,curr_string);
                    //cout<<"Proper Suffix is "<<propar<<endl;
                    curr->Child[i]->FL=Search_In_Trie(propar);
                    if(j<(curr_string.length())-1&&curr->Child[i]->FL==root) // that mean i still have other propers to search it
                        continue;
                    else
                    {
                        // that mean i have search at all propers and does not find any proper in the trie so the FailuerLink is the root nod
                        z=1;
                        curr->Child[i]->FL=Search_In_Trie(propar);

                    }
                }
               // cout<<"Fl is reefer to Node : "<<curr->Child[i]->FL<<endl;
                z=0;
            }

            //cout<<endl;
            Creat_FL(curr->Child[i],curr_string);
            curr_string=real;


        }
    }
}
void Search(Node* root,char* Text) // in this function i will search the location of match of each patterns with the Text
{
    int i=0;
    Node* j=root;
    cout<< "( t "<<i<<","<<" p "<<j->Location<<" ) "<<endl;
    while(i<=strlen(Text))
    {
        if(j->Child[CharToInt[Text[i]]] != NULL  ) // That mean the node have child of this char
        {
            cout<< "( t "<<i+1<<","<<" p "<<j->Child[CharToInt[Text[i]]]->Location<<" ) "; // Here i print the match location
            if(j->Child[CharToInt[Text[i]]]->FL->id !=-1) // here i will print the Rep of each node have Id of each patters
                cout<<" rep ( "<<j->Child[CharToInt[Text[i]]]->FL->id<<" , "<<(i-strlen(pattern[j->Child[CharToInt[Text[i]]]->FL->id]))+1<<" )  ";
            if (j->Child[CharToInt[Text[i]]]->id != -1)
                cout<< " rep ( "<<j->Child[CharToInt[Text[i]]]->id<< " , "<<(i-strlen(pattern[j->Child[CharToInt[Text[i]]]->id]))+1<<" )  ";
            j=j->Child[CharToInt[Text[i]]];
            i++;

            cout<<endl;

        }
        else
        {
            if(j->Location == 0) // That mean i in the index 0 of the Pattern so i have to move the i of Text
                i++;
            else
                j=j->FL; // I will used the FailuerLink of the node to move at it
            cout<< "( t "<<i<<","<<" p "<<j->Location<< " ) "<<endl;
        }

        if(i==strlen(Text) && j->Location==0 ) // this is the base case where i will stop the program
            break;
    }

}
/////////////////////////////////////////////////////////////////////////////////////////////

void Startt()
{
    Text="GAACAAGTGAAGTGAGAAGAAGT";
    InitializeTables();
    InitializeTrie();
    pattern[0]="AGA";
    pattern[1]="AA";
    pattern[2]="AAG";
    pattern[3]="GAAG";
    pattern[4]="TCG";
    int Start=1;
    for(int i=0; i<5; i++)
    {
        InsertRead(pattern[i],i,strlen(pattern[i]),Start);
        Start=CharNum+1;

    }
   Creat_FL(root,"");
   Search(root,Text);
    DeleteTrie();
}

/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Startt();
    return 0;
}

