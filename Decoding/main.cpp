#include <bits/stdc++.h>

using namespace std;

struct node{
    node *lft, *rght, *par;
    char t;
    int wght;
};

int e, r, idx, n;
char cur, flag;
node *root, *NYT;
string deCo, input;

void init(int m){
    root = new node{NULL, NULL, NULL, '&', 0};
    NYT = root;
    idx = 0;
    e = (int) log2(m);
    r = m - (int) pow(2, e);
}

void check(node *cur){
    cur->wght = cur->lft->wght + cur->rght->wght;
    if(cur->rght->wght < cur->lft->wght){
        node *test = cur->lft;
        cur->lft = cur->rght;
        cur->rght = test;
    }
    if(cur->par == NULL) return;
    check(cur->par);
}

void insert(char a){
  NYT->lft = new node{NULL, NULL, NYT, '&', 0};
  NYT->rght = new node{NULL, NULL, NYT, a, 1};
  NYT->t = '-';
  NYT = NYT->lft;
  check(NYT->par);
}

char trace(){
  node *curNode = root;
  while(curNode->t == '-'){
    if(input[idx]=='0')
      curNode = curNode->lft;
    else
      curNode = curNode->rght;
    idx++;
  }
  if(curNode->t != '&'){
    curNode->wght++;
    check(curNode->par);
  }
  return curNode->t;
}

char read(){ //Read E or E+1 bits
  int x = 0;
  int f;
  for(int i=0; i<e; i++){
    f = input[idx] - '0';
    x <<= 1;
    x |= f;
    idx++;
  }
  if(x < r){
    f = input[idx] - '0';
    x <<= 1;
    x |= f;
    idx++;
    x++;
  }
  else{
    x += r + 1;
  }
  return deCo[x-1];
}

int main()
{

  freopen("../Encoding/encoded.txt", "rt", stdin);
  freopen("decoded.txt", "wt", stdout);

  cin >> n;
  cin.ignore();
  char ch;
  getline(cin, deCo);
  init(n);
  cin >> input;
  //read first code symbol
  cur = read();
  insert(cur);
  cout << cur;
  while(idx < input.size()){
    flag = trace();
    if(flag == '&'){ //New Symbol
      cur = read();
      insert(cur);
      cout << cur;
    }
    else{ //Existing Symbol
      cout << flag;
    }
  }

  return 0;
}
