#include <bits/stdc++.h>

using namespace std;

int e, r, n;
string res, test, syms;
map<char, int> enCo;

enum T{
    LFT, RGHT
};

struct node{
    int wght;
    node *lft, *rght, *par;
    T t;
};

node *leaf[200];

void init(int m){
    leaf[0] = new node;
    leaf[0]->wght = 0;
    leaf[0]->lft = leaf[0]->rght = leaf[0]->par = NULL;
    leaf[0]->t = LFT;
    for(int i=1; i<200; i++)
        leaf[i] = NULL;
    e = (int) log2(m);
    r = m - (int) pow(2, e);
}

void insert(char a){
    leaf[0]->lft = new node{0, NULL, NULL, leaf[0], LFT};
    leaf[0]->rght = new node{1, NULL, NULL, leaf[0], RGHT};
    leaf[a] = leaf[0]->rght;
    leaf[0] = leaf[0]->lft;
}

void check(node *cur){
    cur->wght = cur->lft->wght + cur->rght->wght;
    if(cur->rght->wght < cur->lft->wght){
        node *test = cur->lft;
        test->t = RGHT;
        cur->rght->t = LFT;
        cur->lft = cur->rght;
        cur->rght = test;
    }
    if(cur->par == NULL) return;
    check(cur->par);
}

void genCode(node *cur){
    if(cur->par == NULL) return;
    res.push_back('0' + cur->t);
    genCode(cur->par);
}

string symCode(int k){
  string ret = "";
  int tmpE = e;
  int cnt = 0;
  if(k<=2*r){
    k--;
    tmpE++;
  }
  else
    k -= r+1;
  while(cnt<tmpE){
    string x = "";
    x.push_back('0'+(k&1));
    ret.insert(0, x);
    k >>= 1;
    cnt++;
  }
  return ret;
}

int main()
{

  freopen("original.txt", "rt", stdin);
  freopen("encoded.txt", "wt", stdout);

  cin >> n;
  cin.ignore();
  cout << n << endl;
  getline(cin, syms);
  //Map symbols to their k
  for(int i=0; i<syms.size(); i++){
    enCo[syms[i]] = i+1;
  }
  cout << syms << endl;

  init(n);
  getline(cin, test);
  for(auto a: test){
    int k = enCo[a];
    if(leaf[a] == NULL){  //New Symbol
      res = "";
      //Get Code of NYT
      genCode(leaf[0]);
      reverse(res.begin(), res.end());
      //Get Code of K and out the total code
      cout << res << symCode(k);
//      cout << "N: " << res << endl;
//      cout << "C: " << symCode(k) << endl;
      insert(a);
    }
    else{ //Existing Symbol
      res = "";
      //Get Code of existing char in the tree
      genCode(leaf[a]);
      reverse(res.begin(), res.end());
      cout << res;
//      cout << "T: " << res << endl;
      leaf[a]->wght++;
    }
    check(leaf[a]->par);
  }

  return 0;
}
