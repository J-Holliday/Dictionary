// dict.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
#include <ctype.h>
#include <vector>
using namespace std;

/*
  デバッグの際の注意事項：
  [1][プロジェクト]→[dictのプロパティ]→[構成プロパティ]→[コマンド引数]で引数は指定できる。
     しかしこのとき、ダブルクォート囲みでの指定（"break up"等）によって、
	 スペースを含んだ語を一単位の引数として扱うことが出来ない。
	 これはvc++デバッガ上の問題らしく、生成した.exeプログラムではダブルクォート使用が可能である。

*/

/*
* split, vbやrubyにおけるsplitと同義
* @param[in,out] &str 元の文字列の先頭アドレス, delim 分割文字
* @return 分割後のvector<string>コンテナ
*/
vector<string> split(const string &str, char delim){
	vector<string> res;
	size_t current = 0, found;
	while ((found = str.find_first_of(delim, current)) != string::npos){
		res.push_back(string(str, current, found - current));
		current = found + 1;
	}
	res.push_back(string(str, current, str.size() - current));
	return res;
}

/*
* 文字列中の大文字を小文字に変換する
* @param[in,out] s 変換したい文字列
* @return 変換後の文字列 (s) の先頭アドレス
*/
char *ToLowerString(char *s) {
	int i = 0;

	while (s[i] != '\0') {
		s[i] = tolower((unsigned char)s[i]);
		i++;
	}

	return s;
}

int main(int argc, char *argv[])
{
	if (argc == 1) return 0;

	//printf("%d番目の引数 = %s\n", 1, argv[1]);
	
	// 単語か熟語か判定し、モードを分ける
	int mode = NULL;
	char* p_space = " ";
	if (strstr(argv[1], p_space) == NULL) mode = 1;
	else mode = 2;
	
	printf("\n\n====================================================================\n");

	ifstream ifs("C:\\Users\\Tamon\\Documents\\visual studio 2013\\Projects\\dict\\Debug\\gene.txt");
	string str;
	if (ifs.fail())
	{
		std::cerr << "失敗" << std::endl;
		char* buffer;
		buffer = _getcwd(NULL, 0);
		cout << buffer << "がカレントです（現在は絶対パス指定なので、意味はあんまりない）" << endl;
		return -1;
	}

	int count = 0;
	int linecount = 0;
	int outputcount = 0;
	char cstr[512];
	char formatted1[128];
	char formatted2[128];
	sprintf(formatted1, "%s ", argv[1]);
	sprintf(formatted2, " %s", argv[1]);
	char* match;
	int match_strcmp = -1;
	vector<string> ary(10);
	char space = ' ';
	char cary[512];
	char cstr_lower[512];
	char* compared_lower; // formatted1, formatted2, argv[1]に対応する

	while (getline(ifs, str))
	{
		linecount++;
		//cout << linecount << endl;
		sprintf(cstr, "%s", str.c_str());

		/* //デバッグ用
		// char checker[] = argv[1]; // 単語はデバッガ指定の引数でOK
		char checker[] = "break up"; // 熟語はデバッガで指定できないので
		if (strcmp(cstr, checker)==0){
			cout << "matching" << endl;
		}
		*/
		
		
		

		if (count == 0){ //二行連続マッチを避けるため、一度マッチしたら次の行は無条件出力
			
			
			if (mode == 1){ // 単語マッチング
				match = NULL;
				ary = split(cstr, space);
				for (int i = 0; i < ary.size(); i++){
					sprintf(cary, "%s", ary[i].c_str());
					if (_stricmp(cary, argv[1]) == 0){ // 大文字小文字の区別はしない
						match = "matching.";
					}
				}
			}
			else if (mode == 2){ // 熟語マッチング ※安定性に保証なし[1]
				compared_lower = ToLowerString(formatted1);
				match = strstr(cstr, compared_lower); //後ろが空白のときヒット
				compared_lower = ToLowerString(formatted2);
				if (match == NULL) match = strstr(cstr, compared_lower); //前が空白のときヒット
				if (match == NULL) { //完全一致のときヒット
					compared_lower = ToLowerString(argv[1]);
					match_strcmp = strcmp(cstr, compared_lower);
					if (match_strcmp == 0) match = "matching.";
				}
			}

			

			if (match != NULL && linecount % 2 == 1){
				std::cout << str << std::endl;
				count++;
				outputcount++;
			}
		}else if(count == 1){
			std::cout << str << std::endl;
			count = 0;
		}
	}

	if (!outputcount) cout << "Not found..." << endl;

	printf("====================================================================\n\n");

	return 0;
}

/*
[1]かつての単語マッチングコード。出力面での不安定さが提唱され、単語マッチングはsplit仕様に置き換えられた。
   split法では熟語のマッチングが不可能なため、熟語のマッチングも可能であった旧コードを熟語用に復活させた。

*/
