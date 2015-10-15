// dict.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
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
  �f�o�b�O�̍ۂ̒��ӎ����F
  [1][�v���W�F�N�g]��[dict�̃v���p�e�B]��[�\���v���p�e�B]��[�R�}���h����]�ň����͎w��ł���B
     ���������̂Ƃ��A�_�u���N�H�[�g�݂͂ł̎w��i"break up"���j�ɂ���āA
	 �X�y�[�X���܂񂾌����P�ʂ̈����Ƃ��Ĉ������Ƃ��o���Ȃ��B
	 �����vc++�f�o�b�K��̖��炵���A��������.exe�v���O�����ł̓_�u���N�H�[�g�g�p���\�ł���B

*/

/*
* split, vb��ruby�ɂ�����split�Ɠ��`
* @param[in,out] &str ���̕�����̐擪�A�h���X, delim ��������
* @return �������vector<string>�R���e�i
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
* �����񒆂̑啶�����������ɕϊ�����
* @param[in,out] s �ϊ�������������
* @return �ϊ���̕����� (s) �̐擪�A�h���X
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

	//printf("%d�Ԗڂ̈��� = %s\n", 1, argv[1]);
	
	// �P�ꂩ�n�ꂩ���肵�A���[�h�𕪂���
	int mode = NULL;
	char* p_space = " ";
	if (strstr(argv[1], p_space) == NULL) mode = 1;
	else mode = 2;
	
	printf("\n\n====================================================================\n");

	ifstream ifs("C:\\Users\\Tamon\\Documents\\visual studio 2013\\Projects\\dict\\Debug\\gene.txt");
	string str;
	if (ifs.fail())
	{
		std::cerr << "���s" << std::endl;
		char* buffer;
		buffer = _getcwd(NULL, 0);
		cout << buffer << "���J�����g�ł��i���݂͐�΃p�X�w��Ȃ̂ŁA�Ӗ��͂���܂�Ȃ��j" << endl;
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
	char* compared_lower; // formatted1, formatted2, argv[1]�ɑΉ�����

	while (getline(ifs, str))
	{
		linecount++;
		//cout << linecount << endl;
		sprintf(cstr, "%s", str.c_str());

		/* //�f�o�b�O�p
		// char checker[] = argv[1]; // �P��̓f�o�b�K�w��̈�����OK
		char checker[] = "break up"; // �n��̓f�o�b�K�Ŏw��ł��Ȃ��̂�
		if (strcmp(cstr, checker)==0){
			cout << "matching" << endl;
		}
		*/
		
		
		

		if (count == 0){ //��s�A���}�b�`������邽�߁A��x�}�b�`�����玟�̍s�͖������o��
			
			
			if (mode == 1){ // �P��}�b�`���O
				match = NULL;
				ary = split(cstr, space);
				for (int i = 0; i < ary.size(); i++){
					sprintf(cary, "%s", ary[i].c_str());
					if (_stricmp(cary, argv[1]) == 0){ // �啶���������̋�ʂ͂��Ȃ�
						match = "matching.";
					}
				}
			}
			else if (mode == 2){ // �n��}�b�`���O �����萫�ɕۏ؂Ȃ�[1]
				compared_lower = ToLowerString(formatted1);
				match = strstr(cstr, compared_lower); //��낪�󔒂̂Ƃ��q�b�g
				compared_lower = ToLowerString(formatted2);
				if (match == NULL) match = strstr(cstr, compared_lower); //�O���󔒂̂Ƃ��q�b�g
				if (match == NULL) { //���S��v�̂Ƃ��q�b�g
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
[1]���Ă̒P��}�b�`���O�R�[�h�B�o�͖ʂł̕s���肳���񏥂���A�P��}�b�`���O��split�d�l�ɒu��������ꂽ�B
   split�@�ł͏n��̃}�b�`���O���s�\�Ȃ��߁A�n��̃}�b�`���O���\�ł��������R�[�h���n��p�ɕ����������B

*/
