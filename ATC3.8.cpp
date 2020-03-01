
//                                               This is the Algorythm to Code converter
//                                                                       --By Nilanjan Dutta
//                                              Copyright??Um...I don't know.But I am making it  :)
//                                         Project started in 2018....I am in 2nd Year 3rd Sem now
//                                        The reason of making this software is that I want to make
//                                           coding easier for all and algo is the basic need
#include <iostream>
#include<conio.h>
#include <fstream>
#include<bits/stdc++.h>




using namespace std;
ifstream in;//object for reading from the file
ofstream out;//object for writing to a file
string word;//object to check each word
string currentword_str,currentword_str2,sentence;
stringstream *ptr_iss;
string current_line;



char variable[50][50],currentword[2][200];
int i=0,j=0,k=0,p=0,m=0,n=0,current_line_position=0,space_counter_loop=0,z=0;//Do not touch j variable!!!!!!!!
string keywords[]={
                    "print",
                    "show",
                    "display",
                    "while",
                    "for",
                    "if",
                    "else",
                    "get",
                    "take",
                    "fetch",
                    "assign",
                    "scan"
                  };

//Function Definition!!!

int position_of_times(string line);

string before_times(int position);

void upto_times(string stopping_word);

void function_definer(string word);

void $if();

void $else();

void increase();

void decrease();

void $assign();

void spaces();

void processing(string sentence);

int findword(string word,string words[],int limit){
    //cout<<"in findword"<<endl;
     int xx=0,counter=0;
     while(xx<limit){
        if(words[xx]==word){
            //cout<<"Out of findword"<<endl;
            return counter;
        }
        counter++;
        xx++;
     }
     //cout<<"Out of findword"<<endl;
     return -1;

}

void processing(string sentence){
    int xx=0,counter=0,indexy=0,indexx=0,num;//Index is used for the words 2d array so that we can count the number of words
    string converted;
    while(sentence[xx]!=NULL){
        if(sentence[xx]==' '||sentence[xx]==','||sentence[xx]=='='){
            counter++;
        }
        xx++;
    }//For counting total spaces
    //cout<<"First loop cleared"<<endl;

    char words[counter+1][20];
    string str_words[counter+1];
    xx=0;
    while(sentence[xx]!=NULL){
        if(sentence[xx]==' '||sentence[xx]==','||sentence[xx]=='='){
            words[indexy][indexx]=NULL;
            indexx=0;
            indexy++;
        }
        else{
          words[indexy][indexx]=sentence[xx];
          indexx++;
        }
        xx++;
    }
    //cout<<"Second loop cleared"<<endl;
    words[indexy][indexx]=NULL;
    xx=0;

    while(xx<=counter){
        str_words[xx]=words[xx];
        xx++;
    }
    //cout<<"Third loop cleared"<<endl;
    if((num=findword("not",str_words,counter+1))!=-1){
        if(str_words[num+1]=="greater"){
            str_words[num]="<=";
            str_words[num+1]="";
        }
        else if(str_words[num+1]=="less"){
            str_words[num]=">=";
            str_words[num+1]="";
        }
    }
    else if((num=findword("equal",str_words,counter+1))!=-1){
         transform(str_words[0].begin(), str_words[0].end(), str_words[0].begin(), ::tolower);
         if(str_words[0]!="print"&&str_words[0]!="while"&&str_words[0]!="for"&&str_words[0]!="if"&&str_words[0]!="else"&&str_words[0]!="show"&&str_words[0]!="display"){
            if(str_words[1]=="is"){
                str_words[1]="";
                str_words[2]="=";
            }
            else{
                str_words[1]!="=";
            }
            if(str_words[num+1]=="to"){
                str_words[num+1]="";
            }
         }
    }
    else if(str_words[counter]=="{"||str_words[counter]=="["||str_words[counter]=="("){
        str_words[counter]="";
    }

    for(xx=0;xx<=counter;xx++){
        if(str_words[xx]=="="){
            ;
        }
    }
    //cout<<"Converted code part cleared"<<endl;
    for(xx=0;xx<=counter;xx++){
        converted=converted+" "+str_words[xx];
    }
    current_line=converted;
    cout<<current_line<<endl;
}

bool isverb(string word){
string verb="ing";
bool condition=false;
if(word=="is"){
    condition=true;
}
else if(verb.compare(word) < 0){
    condition=true;
}

return condition;
}

int check(string word){
transform(word.begin(), word.end(), word.begin(), ::tolower);


if (word=="print" || word=="write" || word=="echo" || word=="show" || word=="display"){
    return 1;//1 is for print
}//if condition for Print

if (word=="declare"){
    return 2;//2 is for declare
}//if condition for Declare

if (word=="initialise" || word=="define" || word=="initialize"||word=="set"){
    return 3;//3 is for initialisation
}//if condition for Initialisation

if(word=="give"){
    if(current_line.find("value")!=string::npos){
        return 3;
    }
    else{
        return 2;
    }
}

if(word=="scan" || word=="take" || word=="input"|| word=="get"||word=="fetch"){
    if(current_line.find("from")!=string::npos){
        if(current_line.find("user")!=string::npos){
            return 4;//4 is from scanf
        }
        else{
            return 9;
        }
    }
    else{
        return 4;
    }
}//if condition for scanning

if(word=="while" || word=="for"){
    return 5;
}//if condition for while or for loop

if(word=="if"){
    return 6;
}//for if conditions

if(word=="increase"){
    return 7;
}//for increase part

if(word=="decrease"){
    return 8;
}//for decrease part

if(word=="assign" || word=="put" ||word=="place" ||word=="set"){
    return 9;
}
//for assigning values
if(word=="take"){
    if(current_line.find("from")!=string::npos){
        if(current_line.find("user")!=string::npos){
            return 4;
        }
        else{
            return 9;
        }
    }
    else{
        return 4;
    }
}//for the keyword take

}

bool ischar(char charector){
       if(charector>='a' && charector<='z'){
        return true;
       }
       else
         return false;

}

bool isvariable(char variable[50][50],string word,int j){
bool yesvariable=false;
int m=0,p=0;
char char_array[50];
strcpy(char_array, word.c_str());
   for(m=0;m<j;){
                if(!(strcmp(variable[m],char_array))){
                      yesvariable=true;
                      return true;
                      break;
                   }
                m++;
            }

return false;
}

void print(){
int counter=0;
string sentence_to_be_printed="";
            out<<"print (\"";


            while((*ptr_iss)>>word){
                if(counter){
                    out<<" ";
                }
                if(isvariable(variable,word,j)){
                    out<<"\","<<word<<",\" ";

                }
                else if(word=="that"||word=="That"){
                (*ptr_iss)>>word;
                if(isverb(word)){
                    out<<"That "<<word;
                }else
                    out<<word;
                    counter++;
                }

                else{
                  out<<word;
                  counter++;
                }
            }
            out<<" \",end=\"\")"<<endl;
}

void declare(){
out<<"print(\"\")"<<endl;
while((*ptr_iss)>>word){

            if(word!="values" && word!="variables" && word!="and" && word!="," && word!="variable" &&word!="as"){
                    i=0;
                while(word[i]!=NULL){
                    if(word[i]==','){
                            variable[j][k]=NULL;
                        j++;
                        i++;
                        k=0;

                    }
                    else{
                        variable[j][k]=word[i];
                        //cout<<"In the Else:"<<variable[j][k]<<"\n";
                        k++;
                        i++;

                    }

                }


                variable[j][k]=NULL;
                j++;
                k=0;



            }
             /*  else  {
                      iss >> word;
               }
            */
            }
            int m=0,p=0;
            cout<<"Variables initialized are:"<<endl;
            for(m=0;m<j;){
                while(variable[m][p]!=NULL){
                    cout<<variable[m][p];
                    p++;
                }
                p=0;
                cout<<endl;
                m++;
            }

out<<"print(\"\")"<<endl;
}

void initialize(){
out<<"print(\"\")"<<endl;
spaces();
       int found,counter=0;
       string sentence="";
       while((*ptr_iss)>>word){

            if (word=="with" || word=="by"||word=="to"||word=="of"){
                word="=";
            }
            if (word=="and" || word=="And"){
                word=",";
            }
            if(word=="a"||word=="variable"||word=="value"||word=="me"||word=="equal"||word=="is"){
                word="";
            }

          sentence=sentence+" "+word;
          }
       i=1;
       m=0;
       k=0;

       while(sentence[i]!=NULL){
            if(sentence[i]==','){

                currentword[m][k]=NULL;
                currentword_str=currentword[m];
                out<<currentword_str<<endl;
                m=0;
                k=0;
            }
            else if(sentence[i]==' '){
                ;
            }
            else if(sentence[i]=='='){
                currentword[m][k]=NULL;
                currentword_str=currentword[m];
                if(isvariable(variable,currentword_str,j)==false){
                    n=0;
                    while(currentword_str[n]!=NULL){
                        variable[j][n]=currentword_str[n];
                        n++;

                    }
                    variable[j][n]=NULL;

                    currentword_str=variable[j];
                    j++;

                }


                out<<currentword_str<<"=";
                m=1;
                k=0;
            }
            else{

                 if(m==1 && ischar(sentence[i])){
                    while(sentence[i]!=',' && sentence[i]!=NULL){
                        currentword[m][k]=sentence[i];
                        k++;
                        i++;
                     }
                     currentword[1][k]=NULL;
                     currentword_str=currentword[m];
                     if(isvariable(variable,currentword_str,j)){
                        out<<currentword_str<<endl;
                     k=0;
                     m=0;
                     }
                     else{
                      out<<"\""<<currentword_str<<"\""<<endl;
                     k=0;
                     m=0;
                     }
                 }
                 else{
                 currentword[m][k]=sentence[i];
                 k++;
                 }
            }
            i++;
          }
          if(m==1){
                currentword[1][k]=NULL;
                currentword_str=currentword[m];
                out<<currentword_str<<endl;
          }
spaces();
out<<"print(\"\")"<<endl;
}

void spaces(){

int pp=space_counter_loop;
while(pp--){
    out<<"   ";
}
}

void scan(){
out<<"print(\"\")"<<endl;
sentence="";
            while((*ptr_iss)>>word){
                if(word=="in"){
                    (*ptr_iss)>>word;
                }
                if(word=="from"){

                        (*ptr_iss)>>currentword_str;
                        if(currentword_str=="user" || currentword_str=="the"){
                            if(currentword_str=="user"){
                            if((*ptr_iss)>>word){
                                            ;
                                        }
                                        else{
                                            word="";
                                        }
                            }
                            else if(currentword_str=="the"){

                                    (*ptr_iss)>>currentword_str;
                                if(currentword_str=="user"){

                                        if((*ptr_iss)>>word){
                                            ;
                                        }
                                        else{
                                            word="";
                                        }
                                }
                                else{
                                    word="from the "+currentword_str;
                                }
                            }
                        }
                        else{
                            word="from "+currentword_str;
                        }
                }

                if(word=="and"){
                     word=",";
                }


                sentence=sentence+word+" ";

            }

              n=0;
              m=0;



            while(sentence[n]!= NULL){
                if(sentence[n]==' '){

                    ;
                }
                else if(sentence[n]==','){
                        currentword[0][m]=NULL;
                        m=0;
                        currentword_str2=currentword[0];

                        out<<currentword_str2<<"=input(\""<<currentword_str2<<":\")"<<endl;
                        if(isvariable(variable,currentword_str2,j)==false){
                            k=0;
                            while(currentword[0][k]!=NULL){
                                  variable[j][k]=currentword[0][k];
                                  k++;
                            }
                            j++;
                            variable[j][n]=NULL;
                        }
                        spaces();
                        out<<"try:"<<endl;
                        space_counter_loop++;
                        spaces();
                        out<<currentword_str2<<"=int("<<currentword_str2<<")"<<endl;
                        space_counter_loop--;
                        out<<"except ValueError:"<<endl;
                        space_counter_loop++;
                        spaces();
                        out<<"print (\"\",end=\"\")"<<endl;
                        space_counter_loop--;

                }
                else{

                        currentword[0][m]=sentence[n];

                        m++;
                }
                n++;
            }
            currentword[0][m]=NULL;
                        currentword_str2=currentword[0];

                        out<<currentword_str2<<"=input(\""<<currentword_str2<<":\")"<<endl;
                        if(isvariable(variable,currentword_str,j)==false){
                            k=0;
                            while(currentword[0][k]!=NULL){
                                  variable[j][k]=currentword[0][k];
                                  k++;
                            }
                            j++;
                            variable[j][n]=NULL;
                        }

out<<"print(\"\")"<<endl;
spaces();
out<<"try:"<<endl;
space_counter_loop++;
spaces();
out<<currentword_str2<<"=int("<<currentword_str2<<")"<<endl;
space_counter_loop--;
out<<"except ValueError:"<<endl;
space_counter_loop++;
spaces();
out<<"print (\"\",end=\"\")"<<endl;
space_counter_loop--;
}

void bydefault(){

              if(current_line.find('=')==string::npos&&current_line!=""&&current_line!=" "){
                            out<<"#";
                    }

                        out<<word;
                        while((*ptr_iss)>>word){
                            out<<" "<<word;
                        }
                        out<<endl;
word="";
}

void whiile(){
    int genable=0;
    int lenable=0;
    int nenable=0;
 out<<"print(\"\")"<<endl;
 string status_word="hey";
 z=space_counter_loop;
        while(z){
        out<<"   ";
        z--;
        }

 out<<"while ";
 space_counter_loop+=1;
 while(*(ptr_iss)>>word){
     if(word=="is"||word=="than"||word=="to"||word=="("||word=="{"||word=="["){
        *(ptr_iss)>>word;
    }
    if(word=="greater" || word=="more"){
        genable=1;
        word="";
        out<<word;
    }
    else if(word=="less"){
         word="";
        lenable=1;
        out<<word;
    }
    else if(word=="not"){
        word="";
        nenable=1;
        out<<word;
    }
    else if(word=="equal"||word=="equals"){
        if(nenable==1){
                word="!=";
                out<<word;
        }
        else{
            word="==";
            out<<word;
        }
    }
    else if(word=="and" || word=="&&"){
         *(ptr_iss)>>currentword_str;
        if(currentword_str=="equal"||currentword_str=="equals"){
            if(genable==1){
            word=">=";
            genable=0;
            }
            else if(lenable==1){
             word="<=";
             lenable=0;
            }
            else if(nenable==1){
             word="!=";
             nenable=0;
            }
        }
        else{
         if(genable==1) out<<">";
         if(lenable==1) out<<"<";

            cout<<currentword_str<<endl;
        word=" and ";
        out<<word;
        out<<currentword_str;
        genable=0;
        lenable=0;
        continue;
        }
        out<<word;
    }
    else if(word=="or" || word=="||"){
         *(ptr_iss)>>currentword_str;
        if(currentword_str=="equal"||currentword_str=="equals"){
            if(genable==1){
            word=">=";
            genable=0;
            }
            else if(lenable==1){
             word="<=";
             lenable=0;
            }
        }
        else{

         if(genable==1) out<<">";
         if(lenable==1) out<<"<";


        word=" or ";
        out<<word;
        out<<currentword_str;
        genable=0;
        lenable=0;
        continue;
        }
        out<<word;
    }
    else{
        if(genable==1){
            out<<">";
        }
        if(lenable==1){
            out<<"<";
        }
        out<<word;
    }

 }
 out<<":"<<endl;


 while(status_word!="end" && status_word!="End"&& status_word!=")"&& status_word!="}"&& status_word!="]"){

    word="";
    getline(in,current_line);
    processing(current_line);
    stringstream is(current_line);
    ptr_iss=&is;
    *ptr_iss>>word;
     status_word=word;

    if(word=="end"||word=="End"||word==")"||word=="}"||word=="]"){
        break;
    }
    else{
        z=space_counter_loop;
        while(z){
        out<<"   ";
        z--;
        }
        function_definer(word);
    }
    }


space_counter_loop-=1;
spaces();
out<<"print(\"\")"<<endl;
}//while loop function is upto here

int position_of_times(string line){
i=0;

int position=0;
string checking_word;
while(line[i]!=NULL){
    n=0;
    while(line[i]!=' '&& line[i]!=NULL){
        currentword[0][n]=line[i];
        i++;
        n++;
    }
    currentword[0][n]=NULL;
    checking_word=currentword[0];
    position++;
    if(checking_word=="time" || checking_word=="times"){

        return position;

    }
    while(line[i]==' '){
        i++;
    }
}

return -1;
}//Here is the function that gives me the position of the times keyword

string before_times(int position){
//cout<<"in before"<<endl;

i=0;
int counter=0;
string checking_word_final;
while(counter!=position){

     n=0;
     while(current_line[i]!=' ' && current_line[i]!=NULL){
        currentword[0][n]=current_line[i];

        i++;
        n++;
     }
     currentword[0][n]=NULL;
     string string_word(currentword[0]);
     checking_word_final=string_word;

     counter++;
     while(current_line[i]==' '){
        i++;
     }
}

return checking_word_final;
}

void upto_times(int stopping_word){
int counter=0;
string line="",building_words;

i=0;
int xx=0,count_space=0;
while(count_space<stopping_word){
    n=0;
    line=line+" "+building_words;
     while(current_line[i]!=' ' && current_line[i]!=NULL){
        currentword[0][n]=current_line[i];
        i++;
        n++;
     }
     count_space++;
     currentword[0][n]=NULL;
     string string_word(currentword[0]);
     building_words=string_word;

     while(current_line[i]==' '){
        i++;
     }
}
    //cout<<line<<endl;
    stringstream is(line);
    ptr_iss=&is;
    current_line=line;

    *(ptr_iss)>>word;

    switch (check(word)){
               case 1: {
                  print();
            break;
        }

               case 2: {
                  declare();
           break;
        }//declaration of variables

               case 3: {
                  initialize();
          break;
       }//The Initialization part.

               case 4: {
                  scan();
              break;
        }//Scanning part upto here

               case 5: {
                  whiile();
              break;
        }//While loop part upto here

               default :{
                  bydefault();
        }//Default case

       }




}

void $else(){
    out<<"else:"<<endl;
    string status_word="hey";
    space_counter_loop++;
  while(status_word!="end" && status_word!="End"){


    getline(in,current_line);
    stringstream is(current_line);
    ptr_iss=&is;
    *ptr_iss>>word;
     status_word=word;

    if(word=="end"||word=="End"){
        break;
    }
    else {
        spaces();
        function_definer(word);
 }

}

}

void $assign(){
    currentword_str="";
while(*(ptr_iss)>>word){

        if(word=="the"||word=="value"||word=="of"||word=="and"){
            ;
        }
        else{
            *(ptr_iss)>>currentword_str;
            if(currentword_str=="from"){
                *(ptr_iss)>>currentword_str2;
                out<<word<<"="<<currentword_str2<<endl;
                if(!isvariable(variable,word,j)){
                    int pp=0;
                    k=0;
                    while(word[pp]!=NULL){
                        variable[j][k]=word[pp];
                        k++;
                        pp++;
                    }
                    j++;
                }
            }
            else{
                *(ptr_iss)>>currentword_str2;
                out<<currentword_str2<<"="<<word<<endl;
                if(!isvariable(variable,currentword_str2,j)){
                    int pp=0;
                    k=0;
                    while(currentword_str2[pp]!=NULL){
                        variable[j][k]=currentword_str2[pp];
                        k++;
                        pp++;
                    }
                    j++;
                }
            }
        }
   }
}//Assign part

void increase() {
    int flag=1,flag2=1;
while(*(ptr_iss)>>word){
    flag2=1;
   //cout<<word<<":"<<flag<<endl;
    if(word=="and" || word==","){
            out<<endl;
            spaces();
            continue;
        }
    else if(flag==1){
        out<<word<<"="<<word<<"+";
        flag=2;
    }
    else if(flag==2){
        flag=3;
    }
    else if(flag==3){
        int index=0,index2=0;
       // cout<<word<<endl;
        while(index<word.length()){
               // cout<<"In while"<<endl;
            if(word[index]==','){
                currentword[0][index2]=NULL;
                index2=0;
                string word_in_use(currentword[0]);
                out<<word_in_use<<endl;
                spaces();
                flag2=0;
            }
            else{
                currentword[0][index2]=word[index];
                index2++;
                //cout<<"From while "<<currentword[0][index2-1]<<endl;
                flag2=1;
            }
            index++;
        }
        //cout<<index2<<":Index2"<<endl;
        currentword[0][index2]=NULL;
        string word_in_use(currentword[0]);
        //cout<<"Reply from current_word:"<<word_in_use<<endl;
        if(!flag2){
            out<<word_in_use<<"="<<word_in_use<<"+";
            flag=2;
        }
        else{
            out<<word_in_use;
            //cout<<currentword_str2<<endl;
            flag=1;
        }
    }
}
out<<endl;
}//Increase part upto here

void decrease() {
int flag=1,flag2=1;
while(*(ptr_iss)>>word){
    flag2=1;
    //cout<<word<<endl;
    if(word=="and" || word==","){
            out<<endl;
            spaces();
            continue;
        }
    else if(flag==1){
        out<<word<<"="<<word<<"-";
        flag=2;
    }
    else if(flag==2){
        flag=3;
    }
    else if(flag==3){
        int index=0,index2=0;
       // cout<<word<<endl;
        while(index<word.length()){
              //  cout<<"In while"<<endl;
            if(word[index]==','){
                currentword[0][index2]=NULL;
                index2=0;
                string word_in_use(currentword[0]);
                out<<word_in_use<<endl;
                spaces();
                flag2=0;
            }
            else{
                currentword[0][index2]=word[index];
                index2++;
               // cout<<"From while "<<currentword[0][index2-1]<<endl;
                flag2=1;
            }
            index++;
        }
        //cout<<index2<<":Index2"<<endl;
        currentword[0][index2]=NULL;
        string word_in_use(currentword[0]);
       // cout<<"Reply from current_word:"<<word_in_use<<endl;
        if(!flag2){
            out<<word_in_use<<"="<<word_in_use<<"-";
            flag=2;
        }
        else{
            out<<word_in_use;
            //cout<<currentword_str2<<endl;
            flag=1;
        }
    }
}
out<<endl;
}//for the decrease part

void $if(){
int flag=0;
int genable=0;
int lenable=0;
int nenable=0;
string status_word="hey";
out<<"if ";

space_counter_loop+=1;
 while(*(ptr_iss)>>word){
     if(word=="is"||word=="than"||word=="to"||word=="{"||word=="("||word=="["){
        *(ptr_iss)>>word;
    }
    if(word=="greater" || word=="more"){
        genable=1;
        word="";
        out<<word;
    }
    else if(word=="less"){
         word="";
        lenable=1;
        out<<word;
    }
    else if(word=="not"){
        word="";
        nenable=1;
        out<<word;
    }
    else if(word=="equal"||word=="equals"){
        if(nenable==1){
                word="!=";
                out<<word;
        }
        else{
            word="==";
            out<<word;
        }
    }
    else if(word=="and" || word=="&&"){
         *(ptr_iss)>>currentword_str;
        if(currentword_str=="equal"||currentword_str=="equals"){
            if(genable==1){
            word=">=";
            genable=0;
            }
            else if(lenable==1){
             word="<=";
             lenable=0;
            }
            else if(nenable==1){
             word="!=";
             nenable=0;
            }
        }
        else{

         if(genable==1) out<<">";
         if(lenable==1) out<<"<";
            out<<currentword_str;
        word=" && ";
        genable=0;
        lenable=0;
        }
        out<<word;
    }
    else if(word=="or" || word=="||"){
         *(ptr_iss)>>currentword_str;
        if(currentword_str=="equal"||currentword_str=="equals"){
            if(genable==1){
            word=">=";
            genable=0;
            }
            else if(lenable==1){
             word="<=";
             lenable=0;
            }
        }
        else{

         if(genable==1) out<<">";
         if(lenable==1) out<<"<";
            out<<currentword_str;
        word=" || ";
        genable=0;
        lenable=0;
        }
        out<<word;
    }
    else{
        if(genable==1){
            out<<">";
        }
        if(lenable==1){
            out<<"<";
        }
        out<<word;
    }

 }

 out<<":"<<endl;
 here:
 while(status_word!="end" && status_word!="End"&& status_word!=")"&& status_word!="}"&& status_word!="]"){

    word="";
    getline(in,current_line);
    processing(current_line);
    stringstream is(current_line);
    ptr_iss=&is;
    *ptr_iss>>word;
     status_word=word;


    if(word=="end"||word=="End"||word==")"||word=="}"||word=="]"){
        break;
    }
    if(word=="else"){
        spaces();
        out<<"print(\"\")"<<endl;
        space_counter_loop--;
        spaces();
        $else();
        break;
    }
    else{
        spaces();
        function_definer(word);
    }
 }


spaces();
out<<"print(\"\")"<<endl;
space_counter_loop-=1;


}//the if condition function ends here

void function_definer(string word){
    int times_position=position_of_times(current_line);
        if(times_position!=-1){



        currentword_str=before_times(times_position-1);





            out<<"times_variable=0"<<endl;
            z=space_counter_loop;
            while(z){
            out<<"   ";
            z--;
            }
            out<<"print(\"\")"<<endl;
            z=space_counter_loop;
            while(z){
            out<<"   ";
            z--;
            }
            out<<"while times_variable<"<<currentword_str<<":"<<endl;

        space_counter_loop+=1;
        z=space_counter_loop;
        while(z){
        out<<"   ";
        z--;
        }
        upto_times(times_position-1);
        z=space_counter_loop;
        while(z){
        out<<"   ";
        z--;
        }
        out<<"times_variable=times_variable+1"<<endl;
        space_counter_loop-=1;
    }//If Ends here
    else{
        switch (check(word)){
             case 1: {
                  print();
            break;
        }

               case 2: {
                  declare();
           break;
        }//declaration of variables

               case 3: {
                  initialize();
          break;
       }//The Initialization part.

               case 4: {
                  scan();
              break;
        }//Scanning part upto here

               case 5: {
                  whiile();
              break;
        }//While loop part upto here

               case 6: {
                   $if();
                   break;
               }//if condition part

               case 7: {
                   increase();
                   break;
               }//increase part

               case 8: {
                   decrease();
                   break;
               }
               case 9: {
                   $assign();
                   break;
               }

               default :{
                  bydefault();
        }//Default case

        }
    }//Else ends here
}//It decides type of the command




int main(int argc,char* argv[]){




if(argc==1){
    in.open("code.txt");
    char* outFile="code.txt_Converted.py";
    out.open(outFile);
}
else{
    in.open(argv[1]);
    char* outFile=strcat(argv[1],"_Converted.py");//your filename_Converted.py
    out.open(outFile);
}


if(in.fail() || out.fail()){
    cout<<"Failed to open files"<<endl;
    exit(-1);
}

// Here goes the main parts

while(!in.eof()){
    word="";
    getline(in,current_line);
    processing(current_line);
stringstream iss(current_line);
    ptr_iss=&iss;
    iss>>word;

    function_definer(word);


}
in.close();
out.close();
return 0;}
