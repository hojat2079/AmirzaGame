#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;

struct User{
    string username;
    string password;
    int level;
    int coins;
    int extraWord;
    int chance;
};

struct Level{
    string letters;
    int countWord;
    int countExtraWord;
    vector<string> word;
    vector<string> extraWord;
    int section;
    int season;
};
struct LastSeen{
    vector<string> oldWord;
    vector<string> oldExtraWord;
    vector<int> countCharWord;
};

int printMainMenu();

int innerMenu();

void switchInnerMenu(vector<User>& users,int index,vector<Level>& levels,vector<LastSeen>& lastSeens);

void switchLevelMenu(vector<User>& users,int index,vector<Level>& levels,vector<LastSeen>& lastSeens);

void getLevelInFile(vector<Level>& vect);

void getUserInFile(vector<User>& vect);

void getLastSeenInFile(vector<LastSeen>& vect,int size,vector<User>& users,vector<Level>& levels);

void getLevelInStringLine(string line,vector<Level>& vect,int season,int section);

void getUserInStringLine(string line,vector<User>& vect);

void saveUserInFile(vector<User>& vect);

void saveLastSeenInFile(vector<LastSeen>& vect);

void sortByRank(vector<User>& vect,vector<LastSeen>& vect2);

void selectRandomLevel(vector<Level>& vect);

void challenge(Level level);

void signUp(vector<User>& users,vector<Level>& levels,vector<LastSeen>& lastSeens);

void login(vector<User>& users,vector<Level>& levels,vector<LastSeen>& lastSeens);

void editProfile(vector<User>& vect,int index);

void continueGame(vector<User>& users,int index,vector<Level>& levels,vector<LastSeen>& lastSeens);

string randomString(string test);

void randomPriceMenu(vector<User>& users,int index);

void selectStep(vector<User>& users,int index,vector<Level>& levels,int levelIndex,vector<LastSeen>& lastSeens);

int main()
{
    srand(time(0));

    struct vector<Level> levels;
    struct vector<User> users;
    struct vector<LastSeen> lastSeens;

    //get level in list
    getLevelInFile(levels);

    //get User in list
    getUserInFile(users);

    //get last seen user in list
    getLastSeenInFile(lastSeens,users.size(),users,levels);

    int showMenu=true;
    while (showMenu) {
        int itemMenu=printMainMenu();
        system("Cls");
        switch (itemMenu) {
        case 1:
            signUp(users,levels,lastSeens);
            break;
        case 2:
            login(users,levels,lastSeens);
            break;
        case 3:
            sortByRank(users,lastSeens);
            break;
        case 4:
            selectRandomLevel(levels);
            break;
        case 5:
            showMenu=false;
            saveUserInFile(users);
            saveLastSeenInFile(lastSeens);
            break;
        default:
            break;
        }
    }
    return 0;
}

int printMainMenu(){
    int itemMenu;
    cout<<"1.Signup\n2.Login\n3.Rank\n4.Challenge\n5.Exit\n";
    cin>>itemMenu;
    while (itemMenu<1 || itemMenu>5) {
        cout<<"Invalid Input!!\n";
        cout<<"1.Signup\n2.Login\n3.Rank\n4.Challenge\n5.Exit\n";
        cin>>itemMenu;
    }
    return itemMenu;
}

int innerMenu(){
    int itemMenu;
    cout<<"1.Continue game\n2.Choose level\n3.Wheel of Luck\n4.Edit profile\n5.Logout\n";
    cin>>itemMenu;
    while (itemMenu<1 || itemMenu>5) {
        cout<<"Invalid Input!!\n";
        cout<<"1.Continue game\n2.Choose level\n3.Wheel of Luck\n4.Edit profile\n5.Logout\n";
        cin>>itemMenu;
    }
    return itemMenu;
}

void randomPriceMenu(vector<User>& users,int index){
    int itemMenu;
    system("Cls");
    cout<<"chance: "<<users[index].chance<<"\n";
    if(users[index].chance<1){
        cout<<"Not price because chance=0 !\n";
    }else {
        cout<<"1-> 50 Coins (posibility 30%)\n"
              "2-> 70 Coins (posibility 20%)\n"
              "3-> 90 Coins (posibility 20%)\n"
              "2-> 110 Coins (posibility 15%)\n"
              "2-> 150 Coins (posibility 10%)\n"
              "2-> 220 Coins (posibility 5%)\n";
    }
    cout<<"1.select random price \n2.Back\n";
    cin>>itemMenu;
    while (itemMenu<1 || itemMenu>2) {
        cout<<"Invalid Input!!\n";
        cout<<"1.select random price \n2.Back\n";
        cin>>itemMenu;
    }
    if(itemMenu==2)
        return;
    if(itemMenu==1){
        int random=rand()%100;
        switch (random) {
        case 0 ... 29:
            users[index].coins+=50;
            cout<<"you get 50 coins\n";
            break;
        case 30 ... 49:
            users[index].coins+=70;
            cout<<"you get 70 coins\n";
            break;
        case 50 ... 69:
            users[index].coins+=90;
            cout<<"you get 90 coins\n";
            break;
        case 70 ... 84:
            cout<<"you get 110 coins\n";
            users[index].coins+=110;
            break;
        case 85 ... 94:
            cout<<"you get 150 coins\n";
            users[index].coins+=150;
        default:
            cout<<"you get 220 coins\n";
            users[index].coins+=220;
            break;
        }
        users[index].chance--;
    }
}

void switchInnerMenu(vector<User>& users,int index,vector<Level>& levels,vector<LastSeen>& lastSeens){
    int showMenu=true;
    while (showMenu) {
        int itemMenu=innerMenu();
        system("Cls");
        switch (itemMenu) {
        case 1:
            continueGame(users,index,levels,lastSeens);
            break;
        case 2:
            switchLevelMenu(users,index,levels,lastSeens);
            break;
        case 3:
            randomPriceMenu(users,index);
            break;
        case 4:
            editProfile(users,index);
            break;
        case 5:
            showMenu=false;
            break;
        default:
            break;
        }
    }
}

void switchLevelMenu(vector<User>& users,int index,vector<Level>& levels,vector<LastSeen>& lastSeens){
    int mojazLevels=users[index].level;
    int selectLevel;
    if(mojazLevels==levels.size())mojazLevels--;
    cout<<"Enter Level mojaz in range "<<1<<" ... "<<mojazLevels<<endl;
    cin>>selectLevel;
    while (selectLevel>mojazLevels || selectLevel<1) {
        cout<<"invalid Level! \n"<<"Enter Level mojaz in range "<<1<<" ... "<<mojazLevels<<endl;
        cin>>selectLevel;
    }
    if(selectLevel==mojazLevels)
        continueGame(users,index,levels,lastSeens);
    selectStep(users,index,levels,selectLevel-1,lastSeens);
}

void getLevelInFile(vector<Level>& vect){
    fstream myFile("C:\\Users\\Azarakhsh\\Desktop\\levels.txt");
    string line;
    int season=-1;
    int section=0;
    while (getline (myFile, line)) {
        section++;
        if(season==-1){
            season++;
            section=0;
            continue;
        }
        if(line.empty()){
            season++;
            section=0;
            continue;
        }
        getLevelInStringLine(line,vect,season,section);
    }

    myFile.close();
}

void getUserInFile(vector<User>& vect){
    fstream myFile("C:\\Users\\Azarakhsh\\Desktop\\user.txt");
    string line;
    bool firstLine=true;
    while (getline (myFile, line)) {
        if(!firstLine)
            getUserInStringLine(line,vect);

        firstLine=false;
    }

    myFile.close();
}

void getLevelInStringLine(string line,vector<Level>& vect,int season,int section){

    string letters="";
    string tempCountWord="";
    int countWord=0;
    string tempCountExtraWord="";
    int countExtraWord=0;
    vector<string> words;
    vector<string> extraWords;
    for(int i=0;i<line.length();i++){

        //get letters in text
        for(int j=0;line[j]!=' ';j++,i++){
            letters+=line[j];
            i=j;
        }
        //get count word in text
        for(int j=i+1;line[j]!=' ';j++,i++){
            tempCountWord+=line[j];
            i=j;
        }
        countWord=stoi(tempCountWord);

        //get extra count word in text
        for(int j=i+1;line[j]!=' ';j++,i++){
            tempCountExtraWord+=line[j];
            i=j;
        }
        countExtraWord=stoi(tempCountExtraWord);

        //get word in text
        for(int k=0;k<countWord;k++){
            string tempWord="";
            for(int j=i+1;line[j]!=' ' && j<line.size();j++,i++){
                tempWord+=line[j];
                i=j;
            }
            words.push_back(tempWord);
        }

        //get word in text
        for(int k=0;k<countExtraWord;k++){
            string tempWord="";
            for(int j=i+1;line[j]!=' ' &&  j<line.size();j++,i++){
                tempWord+=line[j];
                i=j;
            }
            extraWords.push_back(tempWord);
        }

    }
    Level tempLevel;
    tempLevel.word=words;
    tempLevel.season=season;
    tempLevel.letters=letters;
    tempLevel.section=section;
    tempLevel.extraWord=extraWords;
    tempLevel.countExtraWord=countExtraWord;
    tempLevel.countWord=countWord;

    vect.push_back(tempLevel);

}

void getUserInStringLine(string line,vector<User>& vect){
    string username="";
    string password="";
    string level="";
    string coins="";
    string extraWord="";
    string chance="";

    for(int i=0;i<line.length();i++){

        //get username in text
        for(int j=0;line[j]!=' ' && line[j]!='\t';j++,i++){
            username+=line[j];
        }
        for(;line[i]==' ' || line[i]=='\t';i++);

        //get password in text
        for(int j=i;line[j]!=' '&& line[j]!='\t';j++,i++){
            password+=line[j];
        }
        for(;line[i]==' ' || line[i]=='\t';i++);

        //get level in text
        for(int j=i;line[j]!=' '&& line[j]!='\t';j++,i++){
            level+=line[j];
        }
        for(;line[i]==' ' || line[i]=='\t';i++);

        //get coins in text
        for(int j=i;line[j]!=' '&& line[j]!='\t';j++,i++){
            coins+=line[j];
        }
        for(;line[i]==' ' || line[i]=='\t';i++);

        //get count extra word in text
        for(int j=i;line[j]!=' '&& line[j]!='\t';j++,i++){
            extraWord+=line[j];
        }
        for(;line[i]==' ' || line[i]=='\t';i++);

        //get chance in text
        for(int j=i;line[j]!=' '&& line[j]!='\t' && line.size()>j ;j++,i++){
            chance+=line[j];
        }

        User tempUser;
        tempUser.coins=stoi(coins);
        tempUser.level=stoi(level);
        tempUser.chance=stoi(chance);
        tempUser.extraWord=stoi(extraWord);
        tempUser.username=username;
        tempUser.password=password;

        vect.push_back(tempUser);

    }
}

void saveUserInFile(vector<User>& vect){
    ofstream MyFile("C:\\Users\\Azarakhsh\\Desktop\\user.txt");
    MyFile<<vect.size()<<endl;
    for(int i=0;i<vect.size();i++){
        MyFile<<vect[i].username<<" "<<vect[i].password<<" "<<vect[i].level<<" "
             <<vect[i].coins<<" "<<vect[i].extraWord<<" "
            <<vect[i].chance<<endl;
    }
    MyFile.close();
}
void saveLastSeenInFile(vector<LastSeen>& vect){
    ofstream MyFile("C:\\Users\\Azarakhsh\\Desktop\\lastseen.txt");
    for(int i=0;i<vect.size();i++){
        for(int j=0;j<vect[i].oldWord.size();j++){
            MyFile<<vect[i].oldWord[j]<<" ";
        }
        MyFile<<endl;
        for(int j=0;j<vect[i].oldExtraWord.size();j++){
            MyFile<<vect[i].oldExtraWord[j]<<" ";
        }
        MyFile<<endl;
        for(int j=0;j<vect[i].countCharWord.size();j++){
            MyFile<<vect[i].countCharWord[j]<<" ";
        }
        MyFile<<endl;
    }
    MyFile.close();
}

void sortByRank(vector<User>& vect,vector<LastSeen>& vect2){
    for(int i=1;i<vect.size();i++){
        for(int j=0;j<i;j++){
            if(vect[j].level>vect[i].level){
                User temp=vect[i];
                vect[i]=vect[j];
                vect[j]=temp;
                LastSeen temp2;
                vect2[i]=vect2[j];
                vect2[j]=temp2;
            }
        }
    }

    //print
    for(int i=vect.size()-1;i>=0;i--){
        cout<<vect.size()-i<<". "<<vect[i].username<<"\t "<<vect[i].level<<endl;
    }
}

void selectRandomLevel(vector<Level>& vect){
    int randomLevel=rand()%vect.size();
    challenge(vect.at(randomLevel));
}

void challenge(Level level){
    string player1,player2;
    int score1=0,score2=0;
    cout<<"Enter number player1 : ";
    cin>>player1;
    cout<<"Enter number player2 : ";
    cin>>player2;
    bool turn=0;
    vector<string> oldWord;
    while (oldWord.size()!=level.word.size()+1) {
        system("Cls");
        cout<<"Player1: "<<player1<<"\tscore: "<<score1<<"\tplayer2: "<<
              player2<<"\tscore: "<<score2<<endl;
        cout<<"turn: ";
        if(!turn)cout<<player1<<endl;
        else cout<<player2<<endl;
        for(int i=0;i<level.letters.length();i++){
            cout<<level.letters[i]<<" ";
        }
        cout<<"\n----\n";
        for(int i=0;i<oldWord.size();i++){
            cout<<oldWord[i]<<endl;
            if(i==oldWord.size()-1){
                cout<<"----\n";
            }
        }
        if(oldWord.size()==level.word.size()){
            if(score1>score2){
                cout<<player1<<"  Win!\n";
            }else if(score1<score2) cout<<player2<<"  Win!\n";
            else cout<<"draw!\n";
            break;
        }
        cout<<"if you want go back to main menu enter * : "<<endl;
        if(!turn)cout<<player1<<" ";
        else cout<<player2<<" ";
        cout<<"enter word : ";
        string tempWord;
        cin>>tempWord;
        if(tempWord=="*"){
            if(turn) {
                cout<<player2<<" left the game. "<<player1<<" is win!!\n";
            }else {
                cout<<player1<<" left the game. "<<player2<<" is win!!\n";
            }
            break;
        }
        for(int i=0;i<level.word.size();i++){
            if(tempWord==level.word[i]){
                bool is=false;
                for(int j=0;j<oldWord.size();j++){
                    if(tempWord==oldWord[j]){
                        is=true;
                        break;
                    }
                }
                if(!is){
                    oldWord.push_back(tempWord);
                    if(!turn)score1+=tempWord.size();
                    else score2+=tempWord.size();
                    break;
                }
            }
        }
        turn = !turn;
    }

}

void login(vector<User>& users,vector<Level>& levels,vector<LastSeen>& lastSeens){
    cout<<"Login\nif you want go back to main menu enter * : "<<endl;
    int index;
    string username,password;
    while (true) {
        bool isLogin=false;
        cout<<"username : ";
        cin>>username;
        if(username=="*")
            return;
        cout<<"password : ";
        cin>>password;
        for(int i=0;i<users.size();i++){
            if(users[i].username==username && users[i].password==password){
                isLogin=true;
                index=i;
                break;
            }
        }
        if(!isLogin){
            cout<<"not founded user!!"<<endl;
        }else {
            switchInnerMenu(users,index,levels,lastSeens);
            break;
        }
    }
}

void signUp(vector<User>& users,vector<Level>& levels,vector<LastSeen>& lastSeens){
    cout<<"SignUp\nif you want go back to main menu enter * : "<<endl;
    string username,password;
    while (true) {
        bool isExist=false;
        cout<<"username : ";
        cin>>username;
        if(username=="*")
            return;
        cout<<"password : ";
        cin>>password;
        for(int i=0;i<users.size();i++){
            if(users[i].username==username){
                isExist=true;
                break;
            }
        }
        if(isExist){
            cout<<"user is exits!!"<<endl;
        }else {
            User temp;
            temp.username=username;
            temp.password=password;
            temp.level=1;
            temp.coins=0;
            temp.extraWord=0;
            temp.chance=0;
            users.push_back(temp);
            LastSeen temp2;
            lastSeens.push_back(temp2);
            switchInnerMenu(users,users.size()-1,levels,lastSeens);
            break;
        }
    }
}

void editProfile(vector<User>& vect,int index){
    string password;
    cout<<"Enter password : ";
    cin>>password;
    while (password!=vect.at(index).password) {
        cout<<"invalid password!!"<<endl;
        cout<<"Enter password : ";
        cin>>password;
    }
    string newUsername="",newPassword="";
    cout<<"Enter new username : ";
    cin>>newUsername;
    for(int i=0;i<vect.size();i++){
        if(i==index)
            continue;
        if(vect[index].username==newUsername){
            cout<<"username tekrari ast!!"<<endl;
            cout<<"Enter new username : ";
            cin>>newUsername;
            i=-1;
        }
    }
    cout<<"Enter new password : ";
    cin>>newPassword;
    vect[index].password=newPassword;
    vect[index].username=newUsername;
}

void continueGame(vector<User>& users,int index,vector<Level>& levels,vector<LastSeen>& lastSeens){
    int levelIndex=users[index].level-1;
    if(levelIndex==levels.size()){
        cout<<"finish!!\n";
        return;
    }
    string templetters=levels[levelIndex].letters;
    vector<string> oldWord=lastSeens[index].oldWord;
    vector<string> oldExtraWord=lastSeens[index].oldExtraWord;
    vector<int> countCharWord=lastSeens[index].countCharWord;
    string line;


    //print detail game
    while (oldWord.size()!=levels[levelIndex].word.size()+1) {
        system("Cls");
        cout<<"Season :"<<levels[levelIndex].season<<"\tlevel :"
           <<levels[levelIndex].section<<"\tcoin: "<<users[index].coins
          <<"\t extra words :"<<users[index].extraWord<<endl;
        for(int i=0;i<templetters.length();i++){
            cout<<templetters[i]<<" ";
        }
        cout<<endl<<endl;
        for(int i=0;i<levels[levelIndex].countWord;i++){
            for(int j=0;j<levels[levelIndex].word[i].size();j++){
                for(int k=j;k<countCharWord[i] && countCharWord.size()>i ;k++,j++){
                    cout<<levels[levelIndex].word[i][k];
                }
                if(j!=levels[levelIndex].word[i].size())
                    cout<<"-";
            }
            cout<<"\n";
        }

        //end step
        if(oldWord.size()==levels[levelIndex].word.size()){
            users[index].coins+=100;
            users[index].level++;
            if(levels[users[index].level-1].season>levels[users[index].level-2].season){
                users[index].chance++;
                cout<<"very Good!!\nnext season!! (only PressEneter)!!";
            }
            cout<<"very Good!!\nnext step!! (only PressEneter)!!";
            levelIndex++;
            if(levelIndex==levels.size()){
                cout<<"finish!!\n";
                break;
            }
            cin.get();
            cin.get();
            oldWord.clear();
            templetters=levels[levelIndex].letters;
            countCharWord.clear();
            for(int i=0;i<levels[levelIndex].countWord;i++){
                countCharWord.push_back(0);
            }
            oldExtraWord.clear();
            continue;
        }

        //input new word
        string tempWord;
        cout<<"if you want go back to internal menu enter * :\n";
        cout<<"if you want another order of letters enter $ :\n";
        cout<<"if you need help enter # :\n";
        cout<<"Enter word: ";
        cin>>tempWord;

        //exit to inner menu
        if(tempWord=="*"){
            lastSeens[index].oldWord=oldWord;
            lastSeens[index].oldExtraWord=oldExtraWord;
            lastSeens[index].countCharWord=countCharWord;
            break;
        }

        //random letters
        if(tempWord=="$"){
            templetters=randomString(templetters);
            continue;
        }

        //hint game
        if(tempWord=="#"){
            if(users[index].coins>80){
                users[index].coins-=80;
                int i=0;
                while (countCharWord[i]==levels[levelIndex].word[i].size()) {
                    i++;
                }
                countCharWord[i]++;
                if(countCharWord[i]==levels[levelIndex].word[i].size()){
                    oldWord.push_back(levels[levelIndex].word[i]);
                }

            }else cout<<"coins<80 !\n";
            continue;
        }

        //add word
        for(int i=0;i<levels[levelIndex].word.size();i++){
            if(tempWord==levels[levelIndex].word[i]){
                bool is=false;
                for(int j=0;j<oldWord.size();j++){
                    if(tempWord==oldWord[j]){
                        is=true;
                        break;
                    }
                }
                if(!is){
                    oldWord.push_back(tempWord);
                    countCharWord[i]=tempWord.size();
                    break;
                }
            }
        }

        //add extra word
        for(int i=0;i<levels[levelIndex].extraWord.size();i++){
            if(tempWord==levels[levelIndex].extraWord[i]){
                bool is=false;
                for(int j=0;j<oldExtraWord.size();j++){
                    if(tempWord==oldExtraWord[j]){
                        is=true;
                        break;
                    }
                }
                if(!is){
                    oldExtraWord.push_back(tempWord);
                    users[index].extraWord+=1;
                    if( users[index].extraWord==6){
                        users[index].extraWord=0;
                        users[index].coins+=50;
                    }
                    break;
                }
            }
        }
    }
}

string randomString(string test){
    string result="";
    bool indexs[test.size()];
    for(int i=0;i<test.size();i++){
        indexs[i]=false;
    }
    while (result.size()!=test.size()) {
        int random=rand()%test.size();
        if(indexs[random])
            continue;
        result+=test[random];
        indexs[random]=true;
    }
    return result;
}
void selectStep(vector<User>& users,int index,vector<Level>& levels,int levelIndex,vector<LastSeen>& lastSeens){
    string templetters=levels[levelIndex].letters;
    vector<string> oldWord;
    vector<int> countCharWord(levels[levelIndex].countWord,0);

    //print detail game
    while (oldWord.size()!=levels[levelIndex].word.size()+1) {
        system("Cls");
        cout<<"Season :"<<levels[levelIndex].season<<"\tlevel :"
           <<levels[levelIndex].section<<"\tcoin: "<<users[index].coins
          <<"\t extra words :"<<users[index].extraWord<<endl;
        for(int i=0;i<templetters.length();i++){
            cout<<templetters[i]<<" ";
        }
        cout<<endl<<endl;
        for(int i=0;i<levels[levelIndex].countWord;i++){
            for(int j=0;j<levels[levelIndex].word[i].size();j++){
                for(int k=j;k<countCharWord[i] && countCharWord.size()>i ;k++,j++){
                    cout<<levels[levelIndex].word[i][k];
                }
                if(j!=levels[levelIndex].word[i].size())
                    cout<<"-";
            }
            cout<<"\n";
        }
        //end step
        if(oldWord.size()==levels[levelIndex].word.size()){
            cout<<"very Good!!\nnext step!! (only PressEneter)!!";
            levelIndex++;
            if(levelIndex+1==users[index].level){
                continueGame(users,index,levels,lastSeens);
                return;
            }
            cin.get();
            cin.get();
            oldWord.clear();
            templetters=levels[levelIndex].letters;
            countCharWord.clear();
            for(int i=0;i<levels[levelIndex].countWord;i++){
                countCharWord.push_back(0);
            }
            continue;
        }

        //input new word
        string tempWord;
        cout<<"if you want go back to internal menu enter * :\n";
        cout<<"if you want another order of letters enter $ :\n";
        cout<<"if you need help enter # :\n";
        cout<<"Enter word: ";
        cin>>tempWord;

        //exit to inner menu
        if(tempWord=="*"){
            break;
        }

        //random letters
        if(tempWord=="$"){
            templetters=randomString(templetters);
            continue;
        }

        //hint game
        if(tempWord=="#"){
            if(users[index].coins>80){
                users[index].coins-=80;
                int i=0;
                while (countCharWord[i]==levels[levelIndex].word[i].size()) {
                    i++;
                }
                countCharWord[i]++;
                if(countCharWord[i]==levels[levelIndex].word[i].size()){
                    oldWord.push_back(levels[levelIndex].word[i]);
                }

            }else cout<<"coins<80 !\n";
            continue;
        }

        //add word
        for(int i=0;i<levels[levelIndex].word.size();i++){
            if(tempWord==levels[levelIndex].word[i]){
                bool is=false;
                for(int j=0;j<oldWord.size();j++){
                    if(tempWord==oldWord[j]){
                        is=true;
                        break;
                    }
                }
                if(!is){
                    oldWord.push_back(tempWord);
                    countCharWord[i]=tempWord.size();
                    break;
                }
            }
        }
    }

}
void getLastSeenInFile(vector<LastSeen>& vect,int size,vector<User>& users,vector<Level>& levels){
    fstream myFile("C:\\Users\\Azarakhsh\\Desktop\\lastseen.txt");
    string line;
    int countLine=1;
    for(int i=0;i<size;i++){
        LastSeen temp;
        vect.push_back(temp);
        for(int j=0;j<levels[users[i].level-1].word.size();j++){
            vect[i].countCharWord.push_back(0);
        }
    }
    int sizeLine=0;
    //get last seen in game
    while (getline (myFile, line)) {
        if(countLine>3){
            countLine=1;
            sizeLine++;
        }
        if(countLine==1){
            for(int z=0;z<line.size();z++){
                string temp="";
                for(int z2=z;line[z2]!=' ';z2++,z++){
                    temp+=line[z2];
                }
                vect[sizeLine].oldWord.push_back(temp);
            }
        }else if (countLine==2) {
            for(int z=0;z<line.size();z++){
                string temp="";
                for(int z2=z;line[z2]!=' ';z2++,z++){
                    temp+=line[z2];
                }
                 vect[sizeLine].oldExtraWord.push_back(temp);
            }
        }else if (countLine==3) {
            int k=0;
            for(int z=0;z<line.size();z++){
                string temp="";
                for(int z2=z;line[z2]!=' ';z2++,z++){
                    temp+=line[z2];
                }
                 vect[sizeLine].countCharWord[k]=stoi(temp);
                 k++;
            }
        }
        countLine++;
    }

    myFile.close();
}
