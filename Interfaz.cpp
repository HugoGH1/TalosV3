
#include "Interfaz.h"
#include "TokenType.h"
#include "MostrarError.h"
#include "Simbolos.h"
#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>
#include <msclr/marshal_cppstd.h>

using namespace std;
using namespace System;
using namespace System::Windows::Forms;

#pragma region Variables Globales
std::string cadenaA, linea, TOKEN = "";
std::string ERR = "", formaPalabraR = "",Palabra = "",ERRSIN = "", palabraTemp = "";
int edo, col,colPre = -1, ap_ini,edoAnterior, longitud;
char c, analizado;
int cont_cadena = 0, index = 0, cont_direcc = 100;
bool culmina = false, esReservada = false;
Simbolos simbolo;
std::unordered_map<std::string, Simbolos> tablaSimbolos;
std::vector<std::string> pilaLexemas;
int matriz[26][32] = {
	{  1,  2,  3,506,506,  0,  0,  0,134,  2,  1, 19, 20,  9, 10, 11, 12, 13, 14, 15, 17,127,119,120,121,122,124,123, 21, 25,128,508}, //q0
	{  1,  2,  2,  2,100,100,100,100,100,  2,  1,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,508}, //q1
	{  2,  2,  2,  2,101,101,101,101,101,  2,  2,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,508}, //q2
	{102,102,  3,102,102,102,102,102,  4,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,508},//q3
	{500,500,  5,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,508}, //q4
	{103,103,  5,103,103,103,103,103,103,  6,  6,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,508},//q5
	{501,501,  8,501,501,501,501,501,501,501,501,  7,  7,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,508}, //q6
	{502,502,  8,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,508},//q7
	{104,104,  8,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,508},//q8
	{109,109,109,109,109,109,109,109,109,109,109,109,109,110,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,508},//q9
	{111,111,111,111,111,111,111,111,111,111,111,111,111,112,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,508},//q10
	{113,113,113,113,113,113,113,113,113,113,113,113,113,114,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,508},//q11
	{116,116,116,116,116,116,116,116,116,116,116,116,116,115,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,508},//q12
	{503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,117,503,503,503,503,503,503,503,503,503,503,503,503,503,508},//q13
	{504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,118,504,504,504,504,504,504,504,504,504,504,504,504,508},//q14
	{ 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,505, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,508}, //q15
	{507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,125,507,507,507,507,507,507,507,507,507,507,507,508},//q16
	{ 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,508},//17
	{126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126, 17,126,126,126,126,126,126,126,126,126,126,508},//q18
	{105,105,105,105,105,105,105,105,105,105,105,129,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,508},//q19
	{106,106,106,106,106,106,106,106,106,106,106,106,130,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,508},//q20
	{108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108, 22, 23,108,508},//q21
	{ 22, 22, 22, 22, 22, 22,131, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,508},//q22
	{ 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 23,508},//q23
	{ 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23,132, 24, 23,508},//q24
	{107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,133,107,508}, //q25
};

std::vector <std::vector <int>> matrizPre = {
	{1, 1, 1, 1, 1, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600},
	{601, 2, 3, 4, 5, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
	{6, 7, 7, 7, 7, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602},
	{603, 603, 603, 603, 8, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603},
	{604, 10, 9, 10, 10, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604},
	{605, 11, 18, 18, 18, 18, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 18, 18, 18, 18, 18, 18, 18, 18, 18, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 18, 18, 18, 18, 18, 18, 18, 18, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605},
	{606, 606, 606, 606, 606, 12, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606},
	{607, 607, 607, 607, 607, 13, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 14, 607, 607, 13, 607, 607, 607, 607, 607, 607},
	{608, 608, 608, 608, 608, 15, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608},
	{609, 609, 609, 609, 609, 16, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 17, 609, 16, 609, 609, 609, 609, 609, 609},
	{610, 610, 610, 610, 610, 107, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610},
	{611, 611, 611, 611, 611, 108, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 109, 108, 611, 611, 611, 611, 611, 611},
	{612, 612, 612, 612, 612, 612, 19, 20, 21, 22, 23, 24, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612},
	{613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 25, 26, 27, 28, 29, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613},
	{614, 31, 31, 30, 31, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614},
	{615, 615, 615, 615, 615, 32, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 33, 615, 615, 615, 615, 615, 615, 615},
	{616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 35, 34, 616, 616, 616, 616, 616, 616},
	{617, 617, 617, 617, 617, 36, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 36, 36, 36, 36, 36, 37, 37, 37, 37, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 38, 38, 38, 38, 38, 38, 38, 38, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617},
	{618, 618, 618, 618, 618, 48, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 51, 50, 49, 55, 55, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618},
	{619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 62, 67, 61, 68, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619},
	{620, 620, 620, 620, 620, 48, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620},
	{621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 49, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621},
	{622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 50, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622},
	{623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 51, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623},
	{624, 624, 624, 624, 624, 52, 624, 624, 624, 624, 624, 624, 52, 52, 52, 52, 52, 624, 624, 624, 624, 624, 624, 624, 624, 624, 52, 52, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624},
	{625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 54, 53, 625, 625, 625, 625, 625, 625},
	{626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 55, 55, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626},
	{627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 56, 57, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627},
	{628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 59, 60, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 58, 628, 628, 628, 628, 628, 628, 628, 628},
	{629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 61, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629},
	{630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 62, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630},
	{631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 63, 64, 64, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631},
	{632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 65, 66, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632},
	{633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 67, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633, 633},
	{634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 68, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634, 634},
	{635, 635, 635, 635, 635, 69, 635, 635, 635, 635, 635, 635, 69, 69, 69, 69, 69, 635, 635, 635, 635, 635, 635, 635, 635, 635, 69, 69, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635, 635},
	{636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 70, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 636, 71, 71, 71, 71, 636, 636, 636, 636},
	{637, 637, 637, 637, 637, 72, 637, 637, 637, 637, 637, 637, 72, 72, 72, 72, 72, 637, 637, 637, 637, 637, 637, 637, 637, 637, 72, 72, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637, 637},
	{638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 74, 73, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 638, 74, 74, 74, 74, 638, 638, 638, 638},
	{639, 639, 639, 639, 639, 75, 639, 639, 639, 639, 639, 639, 75, 75, 75, 75, 75, 639, 639, 639, 639, 639, 639, 639, 639, 639, 75, 76, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639, 639},
	{640, 640, 640, 640, 640, 77, 640, 640, 640, 640, 640, 640, 77, 77, 77, 77, 77, 640, 640, 640, 640, 640, 640, 640, 640, 640, 77, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640, 640},
	{641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 79, 79, 78, 78, 78, 78, 78, 78, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 641, 79, 79, 79, 79, 641, 641, 641, 641},
	{642, 642, 642, 642, 642, 80, 642, 642, 642, 642, 642, 642, 80, 80, 80, 80, 80, 642, 642, 642, 642, 642, 642, 642, 642, 642, 80, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642, 642},
	{643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 82, 82, 82, 82, 82, 82, 82, 82, 81, 81, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 643, 82, 82, 82, 82, 643, 643, 643, 643},
	{644, 644, 644, 644, 644, 85, 644, 644, 644, 644, 644, 644, 85, 85, 85, 85, 85, 644, 644, 644, 644, 644, 644, 644, 644, 644, 85, 644, 644, 644, 644, 644, 644, 644, 644, 644, 83, 84, 644, 644, 644, 644, 644, 644, 644, 644, 644, 644, 644, 644, 644, 644, 644, 644, 644, 644, 644, 644, 644, 644},
	{645, 645, 645, 645, 645, 86, 645, 645, 645, 645, 645, 645, 86, 86, 86, 86, 86, 645, 645, 645, 645, 645, 645, 645, 645, 645, 86, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645, 645},
	{646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 87, 88, 89, 90, 646, 646, 646, 646, 646, 646, 646, 646, 646, 646, 91, 91, 91, 91, 646, 646, 646, 646},
	{647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 92, 93, 94, 95, 96, 97, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647, 647},
	{648, 648, 648, 648, 648, 98, 648, 648, 648, 648, 648, 648, 99, 99, 99, 99, 99, 648, 648, 648, 648, 648, 648, 648, 648, 648, 100, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648, 648},
	{649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 101, 649, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 649, 649, 649, 649, 649, 649, 649, 649, 649, 649, 102, 102, 102, 102, 649, 649, 649, 649},
	{650, 650, 650, 650, 650, 103, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 650, 104, 650, 650, 650, 650, 650, 650, 650},
	{651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 651, 106, 105, 651, 651, 651, 651, 651, 651},
};

std::vector <std::vector <int>> producciones = {
	{4, 2, 3},
	{2, 6},
	{2, 5},
	{2, 15},
	{700},
	{3, 1054, 1057, 1058, 1005, 1000},
	{700},
	{1047, 18, 1004},
	{5, 1054, 14, 1051, 1005, 1002},
	{700},
	{6, 1054, 13, 1050, 7, 1001},
	{8, 1005},
	{7, 1053},
	{700},
	{10, 1005},
	{9, 1053},
	{700},
	{700},
	{1006},
	{1007},
	{1008},
	{1009},
	{1010},
	{1011},
	{1012},
	{1013},
	{1014},
	{1015},
	{1016},
	{15, 1048, 18, 6, 1052, 16, 1026, 13, 1051, 1005, 1003},
	{700},
	{17, 13, 1051, 9},
	{700},
	{16, 1053},
	{700},
	{18, 1054, 19},
	{18, 20},
	{700},
	{21},
	{24},
	{23},
	{22},
	{27},
	{31},
	{34},
	{30},
	{35},
	{29, 1005},
	{1052, 11, 1026, 1019},
	{1052, 25, 1026, 1018},
	{36, 1017},
	{26, 36},
	{25, 1053},
	{700},
	{1005, 28},
	{1020},
	{1021},
	{36, 1051},
	{1020},
	{1021},
	{1056, 1052, 36, 1026, 1049, 18, 1024},
	{1044, 33, 32, 18, 1052, 36, 1026, 1022},
	{32, 18, 1052, 36, 1026, 1042},
	{700},
	{18, 1043},
	{700},
	{1045, 18, 1052, 36, 1026, 1023},
	{1046, 18, 1052, 36, 1055, 36, 1026, 1005, 1025},
	{37, 38},
	{36, 1028},
	{700},
	{39, 40},
	{36, 1029},
	{700},
	{41},
	{41, 1027},
	{42, 43},
	{43, 48},
	{700},
	{44, 46},
	{43, 45},
	{700},
	{1036},
	{1037},
	{700},
	{47, 49},
	{46, 1038},
	{46, 1039},
	{46, 1040},
	{46, 1041},
	{700},
	{1030},
	{1031},
	{1032},
	{1033},
	{1034},
	{1035},
	{50, 1005},
	{14},
	{1052, 36, 1026},
	{1052, 51, 1026},
	{700},
	{52, 1005},
	{0},
	{51, 1053},
	{700},
	{12, 1005},
	{11, 1053},
	{700},
};

std::vector <std::vector <int>> prodSem = {
	{4, 2, 3},
	{2, 6},
	{2, 5},
	{2, 15},
	{700},
	{3, 1054, 1057, 1058, 1005, 1000},
	{700},
	{1047, 18, 1004},
	{5, 1054, 14, 1051, 1005, 1002},
	{700},
	{6, 1054, 13, 1050, 7, 1001},
	{8, 2030,1005},
	{7, 2030,1053},
	{700},
	{10,2030,1005},
	{9, 2030,1053},
	{700},
	{700},
	{1006},
	{1007},
	{1008},
	{1009},
	{1010},
	{1011},
	{1012},
	{1013},
	{1014},
	{1015},
	{1016},
	{15, 1048, 18, 6, 1052, 16, 1026, 13, 1051, 1005, 1003},
	{700},
	{17, 13, 1051, 9},
	{700},
	{16, 1053},
	{700},
	{18, 1054, 19},
	{18, 20},
	{700},
	{21},
	{24},
	{23},
	{22},
	{27},
	{31},
	{34},
	{30},
	{35},
	{29, 1005},
	{1052, 11, 1026, 1019},
	{1052, 25, 1026, 1018},
	{36, 1017},
	{26, 36},
	{25, 1053},
	{700},
	{1005, 28},
	{1020},
	{1021},
	{36, 1051},
	{1020},
	{1021},
	{1056, 1052, 36, 1026, 1049, 18, 1024},
	{1044, 33, 32, 18, 1052, 36, 1026, 1022},
	{32, 18, 1052, 36, 1026, 1042},
	{700},
	{18, 1043},
	{700},
	{1045, 18, 1052, 36, 1026, 1023},
	{1046, 18, 1052, 36, 1055, 36, 1026, 1005, 1025},
	{37, 38},
	{36, 1028},
	{700},
	{39, 40},
	{36, 1029},
	{700},
	{41},
	{41, 1027},
	{42, 43},
	{43, 48},
	{700},
	{44, 46},
	{43, 45},
	{700},
	{1036},
	{1037},
	{700},
	{47, 49},
	{46, 1038},
	{46, 1039},
	{46, 1040},
	{46, 1041},
	{700},
	{1030},
	{1031},
	{1032},
	{1033},
	{1034},
	{1035},
	{50, 1005},
	{14},
	{1052, 36, 1026},
	{1052, 51, 1026},
	{700},
	{52, 1005},
	{0},
	{51, 1053},
	{700},
	{12, 1005},
	{11, 1053},
	{700},
};

std::string PalabrasReservadas[31] = {"include","lib","endlib","class","endclass","int","float","char","string","bool","void","if","elseif","else","endif","do","enddo","while","endwhile","read","write","def","const","of","dowhile","for","endfor","function","endfunction","return","to"};

int EstadoDiferente[14] = {100,101,102,103,104,109,111,113,116,126,105,106,108,107};

#pragma endregion

#pragma region Funciones
char Leer_Caracter(System::String^ codespace) {

	if (index >= 0 && index < codespace->Length) {
		analizado = codespace[index];
		index++;
		return analizado;
	}
	else {
		culmina = true;
		return '\0';
	}
}

int relaciona(char c) {
	if (islower(c) && c != 'e')
		return 0;
	if (isupper(c) && c != 'E')
		return 1;
	if (isdigit(c) && c >= '0' && c <= '9')
		return 2;

	switch (c) {
	case '_': return 3; break;
	case '\t': return 5; break;
	case '\n': return 6; break;
	case '\b': return 7; break;
	case ' ': return 7; break;
	case '.': return 8; break;
	case 'E': return 9; break;
	case 'e': return 10; break;
	case '+': return 11; break;
	case '-': return 12; break;
	case '=': return 13; break;
	case '<': return 14; break;
	case '>': return 15; break;
	case '!': return 16; break;
	case '&': return 17; break;
	case '|': return 18; break;
	case '\'': return 19; break;
	case '"': return 20; break;
	case '#': return 21; break;
	case '(': return 22; break;
	case ')': return 23; break;
	case '[': return 24; break;
	case ']': return 25; break;
	case ',': return 26; break;
	case ';': return 27; break;
	case '/': return 28; break;
	case '*': return 29; break;
	case '%': return 30; break;
	case '\0': return 31; break;
	default: return 4; break;
	}
}

void Token(int e) {
	switch (e) {
	case 100: TOKEN = "Palabra reservada \n"; break;
	case 101: TOKEN = "Identificador \n"; break;
	case 102: TOKEN = "Constante Entera \n"; break;
	case 103: TOKEN = "Constante Real \n"; break;
	case 104: TOKEN = "Constante Notación Científica\n"; break;
	case 105: TOKEN = "Suma\n"; break;
	case 106: TOKEN = "Resta\n"; break;
	case 107: TOKEN = "Multiplicación\n"; break;
	case 108: TOKEN = "División\n"; break;
	case 109: TOKEN = "Asignación\n"; break;
	case 110: TOKEN = "Igual Igual\n"; break;
	case 111: TOKEN = "Menor\n"; break;
	case 112: TOKEN = "Menor o Igual\n"; break;
	case 113: TOKEN = "Mayor\n"; break;
	case 114: TOKEN = "Mayor o Igual\n"; break;
	case 115: TOKEN = "Diferente\n"; break;
	case 116: TOKEN = "NOT\n"; break;
	case 117: TOKEN = "AND\n"; break;
	case 118: TOKEN = "OR\n"; break;
	case 119: TOKEN = "Paréntesis abre\n"; break;
	case 120: TOKEN = "Paréntesis cierra\n"; break;
	case 121: TOKEN = "Corchete abre\n"; break;
	case 122: TOKEN = "Corchete cierra\n"; break;
	case 123: TOKEN = "Punto y coma\n"; break;
	case 124: TOKEN = "Coma\n"; break;
	case 125: TOKEN = "Constante Caracter\n"; break;
	case 126: TOKEN = "Constante String\n"; break;
	case 127: TOKEN = "Numeral\n"; break;
	case 128: TOKEN = "Modulus\n"; break;
	case 129: TOKEN = "Incremento Unitario\n"; break;
	case 130: TOKEN = "Decremento Unitario\n"; break;
	case 131: TOKEN = "Comentario de Linea\n"; break;
	case 132: TOKEN = "Comentario Multilinea\n"; break;
	case 133: TOKEN = "Potencia\n"; break;
	case 134: TOKEN = "Punto\n"; break;
	//case 1000: TOKEN = "include"; break; // NO
	}
}

void Error(int e) {
	switch (e) {
	case 500: ERR = "Se esperaba un dígito "; break;
	case 501: ERR = "Se esperaba un signo o dígito "; break;
	case 502: ERR = "Se esperaba un digito "; break;
	case 503: ERR = "Error, se esperaba '&' para AND "; break;
	case 504: ERR = "Error, se esperaba '|' para OR "; break;
	case 505: ERR = "Cte caracter no válida "; break;
	case 506: ERR = "Error, no se esperaba el simbolo "; break;
	case 507: ERR = "Error, se espera un: ' para cte caracter"; break;
	case 508: ERR = "EoF \n"; break;
	//case 509: ERR = "El archivo está vacío \n"; break;
	}
}

enum ColumnasPredictiva {
	include = 0,
	def = 1,
	const_ = 2,
	function = 3,
	class_ = 4,
	id = 5,
	int_type = 6,
	float_type = 7,
	char_type = 8,
	string_type = 9,
	bool_type = 10,
	void_type = 11,
	cte_entera = 12,
	cte_real = 13,
	cte_notacion = 14,
	cte_caracter = 15,
	cte_string = 16,
	return_ = 17,
	write = 18,
	read = 19,
	incremento = 20,
	decremento = 21,
	if_ = 22,
	while_ = 23,
	do_ = 24,
	for_ = 25,
	par_abre = 26,
	not_ = 27,
	or_ = 28,
	and_ = 29,
	igual_igual = 30,
	diferente = 31,
	menor = 32,
	menor_igual = 33,
	mayor = 34,
	mayor_igual = 35,
	suma = 36,
	resta = 37,
	multiplicacion = 38,
	division = 39,
	modulus = 40,
	potencia = 41,
	elseif_ = 42,
	else_ = 43,
	endif = 44,
	endwhile = 45,
	endfor = 46,
	endclass = 47,
	endfunction = 48,
	dowhile = 49,
	of = 50,
	asignacion = 51,
	par_cierra = 52,
	coma = 53,
	punto_y_coma = 54,
	to = 55,
	enddo = 56,
	lib = 57,
	punto = 58,
	eof = 59 // $ (fin de archivo)
};

#pragma endregion

#pragma region Semantico
void AccionId1(const std::string& lexema) {
	if (tablaSimbolos.count(lexema)) // El identificador ya existe en la tabla de símbolos
		std::cerr << "Error: Identificador '" << lexema << "' ya declarado." << std::endl;
	else
		pilaLexemas.push_back(lexema);
}

void AccionId2(const std::string& tipo) {
	while (!pilaLexemas.empty()) {
		std::string lexema_act = pilaLexemas.back();
		pilaLexemas.pop_back();

		int nuevaDirecc = cont_direcc++;
		Simbolos nuevoSimbolo = { tipo, nuevaDirecc };

		if (!tablaSimbolos.count(lexema_act))  // Insertar en la tabla de simbolos solo si no hay redeclaracion
			tablaSimbolos.emplace(lexema_act, nuevoSimbolo);
	}
}

#pragma endregion

#pragma region Lexico
void TalosV3::Interfaz::Analiza(TalosV3::Interfaz^ form)
{
	System::String^ codespace = form->CodeSpace->Text;
	codespace += " ";
	index = 0;
	cont_cadena = 0;
	culmina = false;
	TOKEN = "";
	ERR = "";
	edo = 0;
	Palabra = "";
	form->TokenSpace->Clear();
	form->ErrorsSpaces->Clear();

	while (cont_cadena < codespace->Length)
	{
		edo = 0;
		culmina = false;
		ap_ini = index;
		while (edo <= 25 && !culmina)
		{
			c = Leer_Caracter(codespace);
			col = relaciona(c);
			if (col == 0 || col == 1 || edo == 1 && col == 3 || edo == 2 && col == 3 || (edo == 2 && col == 10) || (edo == 2 && col == 9) || (edo == 0 && col == 10) || (edo == 0 && col == 9) || (edo == 1 && col == 9) || (edo == 1 && col == 10)) { // palabras mayusculas y _ para identificadores
				Palabra += c;
			}
			edoAnterior = edo; // Guardamos el estado anterior para por si debemos mostrar el eof o si el estado anterior es un error
			edo = matriz[edo][col];

			cont_cadena++;

		}
        if (edo >= 100 && edo <= 134) {
			for (int dif : EstadoDiferente) {
				if (edo == dif) {
					Token(edo);
					index--;
					cont_cadena--;
					longitud = index - ap_ini;
					System::String^ lexema = codespace->Substring(ap_ini, longitud);
					break; // Cuando ya encontró el estado de la palbra reservada, lo saco para ya no repetir el ciclo
				}
			}
			if (edo == 100 || edo == 101) {
				esReservada = false;
				for (int i = 0; i < std::size(PalabrasReservadas); i++) {
					if (Palabra == PalabrasReservadas[i]) {
						Token(100); // Es para cuando se compara la cadena con una palabra reservada válida
						longitud = index - ap_ini;
						System::String^ lexema = codespace->Substring(ap_ini, longitud)->Trim();
						System::String^ lexemaFormato = ("'" + lexema + "'")->PadRight(20);
						form->TokenSpace->AppendText(lexemaFormato+gcnew System::String(TOKEN.c_str())+"\n");
						esReservada = true;
						Palabra = "";
						break;	
					}
				}
				
				if (!esReservada && !Palabra.empty()) {
					Token(101); // Es para enviar el token como identificador
					longitud = index - ap_ini;
					System::String^ lexema = codespace->Substring(ap_ini, longitud)->Trim();
					System::String^ lexemaFormato = ("'" + lexema + "'")->PadRight(20);
					form->TokenSpace->AppendText(lexemaFormato + gcnew System::String(TOKEN.c_str()) + "\n");
					Palabra = "";
				}

			}else {
				Token(edo); // estado de aceptación, entera, flotante
				longitud = index - ap_ini;
				System::String^ lexema = codespace->Substring(ap_ini, longitud)->Trim();
				System::String^ lexemaFormato = ("'" + lexema + "'")->PadRight(20);
				form->TokenSpace->AppendText(lexemaFormato + gcnew System::String(TOKEN.c_str()) + "\n");
				Palabra = "";
			}
		}
		else if (edo >= 500 && edo <= 510) {
			longitud = index - ap_ini;
			System::String^ lexema = codespace->Substring(ap_ini, longitud)->Trim();
			if (codespace->Length <= 1) {
				//Error(509); // Se encontró un error
				form->ErrorsSpaces->AppendText(gcnew System::String("El archivo está vacío" + "\n"));
			}
			else if (edo == 508) {
				if (edoAnterior == 23 || edoAnterior == 24) {
					//Error(510); // Commentario de bloque no terminado
					System::String^ lexemaFormato = ("Error: Comentario de bloque no terminado, cerca de: " + lexema + "")->PadRight(20);
					form->ErrorsSpaces->AppendText(gcnew System::String(ERR.c_str()) + lexemaFormato + "\n");
				}
				else if (edoAnterior == 17) {
					// Constante string no terminada
					System::String^ lexemaFormato = ("Error: Faltan ' \" ' para cte string, cerca de: " + lexema + "")->PadRight(20);
					form->ErrorsSpaces->AppendText(gcnew System::String(ERR.c_str()) + lexemaFormato + "\n");
				}
				Error(edo); // EoF
				form->ErrorsSpaces->AppendText(gcnew System::String(ERR.c_str()) + "\n");
			}
			else {
				if (edo == 506) {
					Error(edo); // Se encontró un error
					System::String^ lexemaFormato = (" cerca de: " + lexema + "")->PadRight(20);
					form->ErrorsSpaces->AppendText(gcnew System::String(ERR.c_str()) + lexemaFormato + "\n");
					//break;
				}
				else {
					Error(edo); // Se encontró un error
					System::String^ lexemaFormato = (" cerca de: " + lexema + "")->PadRight(20);
					form->ErrorsSpaces->AppendText(gcnew System::String(ERR.c_str()) + lexemaFormato + "\n");
					Palabra = "";

					if (index > 0) index--;
					if (cont_cadena > 0) cont_cadena--;
					culmina = true;

					continue;
				}
				
			}
		}
	}
}

static Tokenizador GetNextToken(System::String^ codespace)
{
	Tokenizador token;
	codespace += " ";
	//index = 0;
	//cont_cadena = 0;
	culmina = false;
	TOKEN = "";
	ERR = "";
	edo = 0;
	Palabra = "";

	while (cont_cadena < codespace->Length)
	{
		edo = 0;
		culmina = false;
		ap_ini = index;
		while (edo <= 25 && !culmina)
		{
			c = Leer_Caracter(codespace);
			col = relaciona(c);
			if (col == 0 || col == 1 || edo == 1 && col == 3 || edo == 2 && col == 3 || (edo == 2 && col == 10) || (edo == 2 && col == 9) || (edo == 0 && col == 10) || (edo == 0 && col == 9) || (edo == 1 && col == 9) || (edo == 1 && col == 10)) { // palabras mayusculas y _ para identificadores
				Palabra += c;
			}
			edoAnterior = edo; // Guardamos el estado anterior para por si debemos mostrar el eof o si el estado anterior es un error
			edo = matriz[edo][col];

			cont_cadena++;

		}
		if (edo >= 100 && edo <= 134) {
			for (int dif : EstadoDiferente) {
				if (edo == dif) {
					Token(edo);
					index--;
					cont_cadena--;
					//longitud = index - ap_ini;
					//System::String^ lexema = codespace->Substring(ap_ini, longitud);
					break; // Cuando ya encontró el estado de la palbra reservada, lo saco para ya no repetir el ciclo
				}
			}
			if (edo == 100 || edo == 101) {
				esReservada = false;
				for (int i = 0; i < std::size(PalabrasReservadas); i++) {
					if (Palabra == PalabrasReservadas[i]) {
						Token(100); // Es para cuando se compara la cadena con una palabra reservada válida
						//longitud = index - ap_ini;
						esReservada = true;
						
						//System::String^ lex = codespace->Substring(ap_ini, longitud)->Trim();
						Token(edo);
						System::String^ lex = "";
						for (int i = ap_ini; i < index; ++i)  // Esta parte es para obtener la subcadena o el lexema sin usar Substring
							lex += codespace[i];
						lex = lex->Trim();
						token.lexema = msclr::interop::marshal_as<string>(lex);
						token.edo = edo;
						token.gramema = TOKEN;
						palabraTemp = Palabra;
						Palabra = "";
						return token;
						break;
					}
				}

				// AQUI DEBEMOS PONER LA PARTE DONDE ES UNA RESERVADA PERO DEBEMOS COMPARAR EL EDO CON LOS TIPOS DISPONIBLES PARA LUEGO MANDAR A LLAMAR A AccionId2
				/*if (esReservada && (edo == 100)) {
					if (palabraTemp == "int" || palabraTemp == "float" || palabraTemp == "char" || palabraTemp == "string" || palabraTemp == "bool" || palabraTemp == "void") {
						AccionId2(palabraTemp);
					}
				}*/


				if (!esReservada && !Palabra.empty()) {
					edo = 101; // Si no es una palabra reservada, se considera un identificador
					Token(edo); // Es para enviar el token como identificador
					//longitud = index - ap_ini;
					//System::String^ lex = codespace->Substring(ap_ini, longitud)->Trim();
					token.edo = edo;
					System::String^ lex = "";
					for (int i = ap_ini; i < index; ++i)
						lex += codespace[i];
					lex = lex->Trim();
					token.lexema = msclr::interop::marshal_as<string>(lex);
					//token.lexema = msclr::interop::marshal_as<string>(lex);
					Token(edo);
					token.gramema = TOKEN;
					palabraTemp = Palabra;
					AccionId1(token.lexema);
					Palabra = "";
					return token;
				}

			}
			else {
				Token(edo); // estado de aceptación, entera, flotante
				//longitud = index - ap_ini;
				//System::String^ lex = codespace->Substring(ap_ini, longitud)->Trim();
				token.edo = edo;
				//token.lexema = msclr::interop::marshal_as<string>(lex);
				Token(edo);
				System::String^ lex = "";
				for (int i = ap_ini; i < index; ++i)
					lex += codespace[i];
				lex = lex->Trim();
				token.lexema = msclr::interop::marshal_as<string>(lex);
				token.gramema = TOKEN;
				palabraTemp = Palabra;
				Palabra = "";
				return token;
			}
		}
		else if (edo >= 500 && edo <= 510) {
			//longitud = index - ap_ini;
			//System::String^ lex = codespace->Substring(ap_ini, longitud)->Trim();
			System::String^ lex = "";
			for (int i = ap_ini; i < index; ++i)
				lex += codespace[i];
			lex = lex->Trim();
			
			if (codespace->Length <= 1) {
				//Error(509); // Se encontró un error
				token.edo = edo;
				token.lexema = msclr::interop::marshal_as<string>(lex);
				token.gramema = "El archivo está vacío";
				return token;
			}
			else if (edo == 508) {
				if (edoAnterior == 23 || edoAnterior == 24) {
					token.edo = edo;
					token.lexema = msclr::interop::marshal_as<string>(lex);
					token.gramema = msclr::interop::marshal_as<string>("Error: Comentario de bloque no terminado, cerca de: " + lex + "");
					return token;
				}
				else if (edoAnterior == 17) {
					// Constante string no terminada
					token.edo = edo;
					token.lexema = msclr::interop::marshal_as<string>(lex);
					token.gramema = msclr::interop::marshal_as<string>("Error: Faltan ' \" ' para cte string, cerca de: " + lex + "");
						
					return token;
				}
				Error(edo); // EoF
			}
			else {
				if (edo == 506) {
					token.edo = edo;
					token.lexema = msclr::interop::marshal_as<string>(lex);
					Error(edo);
					token.gramema = msclr::interop::marshal_as<string>(ERROR + " cerca de " + lex + "");
					return token;
				}
				else {
					token.edo = edo;
					token.lexema = msclr::interop::marshal_as<string>(lex);
					Error(edo);
					//ERROR + " cerca de " + lex + ""
					token.gramema = msclr::interop::marshal_as<string>(ERROR + " cerca de " + lex + "");
					palabraTemp = Palabra;
					Palabra = "";
					return token;
					if (index > 0) index--;
					if (cont_cadena > 0) cont_cadena--;
					culmina = true;

					continue;
				}

			}
		}
	}
	token.edo = 508;
	token.lexema = "Eof";
	token.gramema = '\0';
	return token;
}

#pragma endregion

#pragma region Sintactico
int relacionaTokenMatrizPre(int estadoLex, std::string palabra) {
	int indiceColumnaMatriz = -1;

	switch (estadoLex) {
	case 100: // Palabras reservadas (requieren verificación por 'palabra')
		if (palabra == "include") {
			colPre = 1000;
			indiceColumnaMatriz = include;
		}
		else if (palabra == "def") {
			colPre = 1001;
			indiceColumnaMatriz = def;
		}
		else if (palabra == "const") {
			colPre = 1002;
			indiceColumnaMatriz = const_;
		}
		else if (palabra == "function") {
			colPre = 1003;
			indiceColumnaMatriz = function;
		}
		else if (palabra == "class") {
			colPre = 1004;
			indiceColumnaMatriz = class_;
		}
		else if (palabra == "int") {
			colPre = 1006;
			indiceColumnaMatriz = int_type;
		}
		else if (palabra == "float") {
			colPre = 1007;
			indiceColumnaMatriz = float_type;
		}
		else if (palabra == "char") {
			colPre = 1008;
			indiceColumnaMatriz = char_type;
		}
		else if (palabra == "string") {
			colPre = 1009;
			indiceColumnaMatriz = string_type;
		}
		else if (palabra == "bool") {
			colPre = 1010;
			indiceColumnaMatriz = bool_type;
		}
		else if (palabra == "void") {
			colPre = 1011;
			indiceColumnaMatriz = void_type;
		}
		else if (palabra == "return") {
			colPre = 1017;
			indiceColumnaMatriz = return_;
		}
		else if (palabra == "write") {
			colPre = 1018;
			indiceColumnaMatriz = write;
		}
		else if (palabra == "read") {
			colPre = 1019;
			indiceColumnaMatriz = read;
		}
		else if (palabra == "if") {
			colPre = 1022;
			indiceColumnaMatriz = if_;
		}
		else if (palabra == "while") {
			colPre = 1023;
			indiceColumnaMatriz = while_;
		}
		else if (palabra == "do") {
			colPre = 1024;
			indiceColumnaMatriz = do_;
		}
		else if (palabra == "for") {
			colPre = 1025;
			indiceColumnaMatriz = for_;
		}
		else if (palabra == "elseif") {
			colPre = 1042;
			indiceColumnaMatriz = elseif_;
		}
		else if (palabra == "else") {
			colPre = 1043;
			indiceColumnaMatriz = else_;
		}
		else if (palabra == "endif") {
			colPre = 1044;
			indiceColumnaMatriz = endif;
		}
		else if (palabra == "endwhile") {
			colPre = 1045;
			indiceColumnaMatriz = endwhile;
		}
		else if (palabra == "endfor") {
			colPre = 1046;
			indiceColumnaMatriz = endfor;
		}
		else if (palabra == "endclass") {
			colPre = 1047;
			indiceColumnaMatriz = endclass;
		}
		else if (palabra == "endfunction") {
			colPre = 1048;
			indiceColumnaMatriz = endfunction;
		}
		else if (palabra == "dowhile") {
			colPre = 1049;
			indiceColumnaMatriz = dowhile;
		}
		else if (palabra == "of") {
			colPre = 1050;
			indiceColumnaMatriz = of;
		}
		else if (palabra == "to") {
			colPre = 1055;
			indiceColumnaMatriz = to;
		}
		else if (palabra == "enddo") {
			colPre = 1056;
			indiceColumnaMatriz = enddo;
		}
		else if (palabra == "lib") {
			colPre = 1057;
			indiceColumnaMatriz = lib;
		}
		else { // Si es estadoLex 100 pero la palabra no coincide con una reservada
			colPre = -1;
			indiceColumnaMatriz = -1;
		}
		break;

	case 101: colPre = 1005; indiceColumnaMatriz = id; break;
	case 102: colPre = 1012; indiceColumnaMatriz = cte_entera; break;
	case 103: colPre = 1013;indiceColumnaMatriz = cte_real; break;
	case 104: colPre = 1014; indiceColumnaMatriz = cte_notacion; break;
	case 125: colPre = 1015; indiceColumnaMatriz = cte_caracter; break;
	case 126: colPre = 1016; indiceColumnaMatriz = cte_string; break;
	case 129: colPre = 1020; indiceColumnaMatriz = incremento; break;
	case 130: colPre = 1021;indiceColumnaMatriz = decremento; break;
	case 119: colPre = 1026;indiceColumnaMatriz = par_abre; break;
	case 116: colPre = 1027;indiceColumnaMatriz = not_; break;
	case 118: colPre = 1028;indiceColumnaMatriz = or_; break;
	case 117: colPre = 1029;indiceColumnaMatriz = and_; break;
	case 110: colPre = 1030;indiceColumnaMatriz = igual_igual; break;
	case 115: colPre = 1031;indiceColumnaMatriz = diferente; break;
	case 111: colPre = 1032;indiceColumnaMatriz = menor; break;
	case 112: colPre = 1033;indiceColumnaMatriz = menor_igual; break;
	case 113: colPre = 1034;indiceColumnaMatriz = mayor; break;
	case 114: colPre = 1035;indiceColumnaMatriz = mayor_igual; break;
	case 105: colPre = 1036;indiceColumnaMatriz = suma; break;
	case 106: colPre = 1037;indiceColumnaMatriz = resta; break;
	case 107: colPre = 1038;indiceColumnaMatriz = multiplicacion; break;
	case 108: colPre = 1039;indiceColumnaMatriz = division; break;
	case 128: colPre = 1040;indiceColumnaMatriz = modulus; break;
	case 133: colPre = 1041;indiceColumnaMatriz = potencia; break;
	case 109: colPre = 1051;indiceColumnaMatriz = asignacion; break;
	case 120: colPre = 1052;indiceColumnaMatriz = par_cierra; break;
	case 124: colPre = 1053;indiceColumnaMatriz = coma; break;
	case 123: colPre = 1054;indiceColumnaMatriz = punto_y_coma; break;
	case 134: colPre = 1058;indiceColumnaMatriz = punto; break;
	case 508: colPre = 1059;indiceColumnaMatriz = eof; break;

	default: // estado no reconocido o no mapeado a ninguna columna
		colPre = -1; indiceColumnaMatriz = -1; break;
	}

	return indiceColumnaMatriz; // Retorna el índice de columna real de la matrizPre (0-59)
}

void ErroresSin(int e) {
	switch (e) {
	case 508: ERRSIN = "Se esperaba un Fin de Archivo (EoF)."; break;
	case 600: ERRSIN = "Token inesperado al inicio del programa, se esperaba un [include, def, const, function, class]."; break;
	case 601: ERRSIN = "Se esperaba una declaracion como: (def, const, function, class)."; break;
	case 602: ERRSIN = "Se esperaba include para declaracion de librerias, o se esperaba [def, const, function, class]."; break;
	case 603: ERRSIN = "Se espera class para la definicion de una clase."; break;
	case 604: ERRSIN = "Se esperaba la defincion de una constante [const], o se esperaba [def, function, class]."; break;
	case 605: ERRSIN = "Se esperaba def para la definicion de variable, o se esperaba const, function, class, identificador, return, write, read, ++, --, if, while, do, for, endclass, endfunction, dowhile, elseif, else, endif, endwhile, endfor]."; break;
	case 606: ERRSIN = "Se esperaba un identificador válido."; break;
	case 607: ERRSIN = "Se esperaba ' , identificador ' para la definicion de más de un identificador, o se esperaba [of]."; break;
	case 608: ERRSIN = "Se esperaba un identificador válido."; break;
	case 609: ERRSIN = "Se esperaba ' , identificador ' para la definicion de más de un identificador, o se esperaba [=]."; break;
	case 610: ERRSIN = "Se esperaba un identificador válido."; break;
	case 611: ERRSIN = "Se esperaba ' , identificador ' para la definición de más de un identificador, o se esperaba [)]."; break;
	case 612: ERRSIN = "Tipo de dato no valido, se esperaba un tipo de dato (int, float, char, string, bool o void)."; break;
	case 613: ERRSIN = "Se esperaba una constante (cteentera, ctereal, ctenotacion, ctecaracter o ctestring)."; break;
	case 614: ERRSIN = "Se esperaba function para iniciar la definicion de la funcion, o se esperaba [def, const, class]."; break;
	case 615: ERRSIN = "Se esperaba un identificador valido como parametro, o se esperaba [)]."; break;
	case 616: ERRSIN = "Se esperaba una secuencia valida para definir más de un parámetro."; break;
	case 617: ERRSIN = "Se esperaba un [identificador, return, write, read,++,--, ] o una sentencia [if, while,do,for, endclass, endfunction, dowhile, elseif, else, endif, endwhile, endfor] ."; break;
	case 618: ERRSIN = "Se esperaba un [identificador, return, write, read, ++,--]."; break;
	case 619: ERRSIN = "Se esperaba una sentencia[if, while,do,for]."; break;
	case 620: ERRSIN = "Se esperaba un [identificador]."; break;
	case 621: ERRSIN = "Se esperaba la sentencia read."; break;
	case 622: ERRSIN = "Se esperaba la sentencia write."; break;
	case 623: ERRSIN = "Se esperaba la sentencia return."; break;
	case 624: ERRSIN = "Para la expresion se esperaba un [ identificador, cteentera, ctereal, ctenotacion, ctecaracter, ctestring, (, ! ]."; break;
	case 625: ERRSIN = "Se esperaba la secuencia correcta [, ] para definir varias expresiones o se esperaba [)]."; break;
	case 626: ERRSIN = "Se esperaba un [++ ó --]."; break;
	case 627: ERRSIN = "Se esperaba un [++ ó --]."; break;
	case 628: ERRSIN = "Se esperaba un [++, -- ó =]."; break;
	case 629: ERRSIN = "Se esperaba la sentencia do."; break;
	case 630: ERRSIN = "Se esperaba la sentencia if."; break;
	case 631: ERRSIN = "Se esperaba un [elseif, else, endif]."; break;
	case 632: ERRSIN = "Se esperaba un [else, endif]."; break;
	case 633: ERRSIN = "Se esperaba la sentencia while."; break;
	case 634: ERRSIN = "Se esperaba la sentencia for."; break;
	case 635: ERRSIN = "Se esperaba un [identificador, cteentera, ctereal, ctenotacion, ctecaracter, ctestring, (, !]."; break;
	case 636: ERRSIN = "Se esperaba un operador [||, ; , , , ), to]."; break;
	case 637: ERRSIN = "Se esperaba un [identificador, cteentera, ctereal, ctenotacion, ctecaracter, ctestring, (, !]."; break;
	case 638: ERRSIN = "Se esperaba un operador [&&, ||,  ;,  , ,  ),  to]. *"; break;
	case 639: ERRSIN = "Se esperaba un [identificador, cteentera, ctereal, ctenotacion, ctecaracter, ctestring, (, !]."; break;
	case 640: ERRSIN = "Se esperaba un [identificador, cteentera, ctereal, ctenotacion, ctecaracter, ctestring, (]."; break;
	case 641: ERRSIN = "Se esperaba un operador [==, !=, <, <=, >, >=, &&, ||, ;, , , ), to]."; break;
	case 642: ERRSIN = "Se esperaba un [identificador, cteentera, ctereal, ctenotacion, ctecaracter, ctestring, (]."; break;
	case 643: ERRSIN = "Se esperaba un operador [ +, -, ==, !=, <, <=, >, >=, &&, ||, ;, ,, ), to]."; break;
	case 644: ERRSIN = "Se esperaba un [+, -, identificador, cteentera, ctereal, ctenotacion, ctecaracter, ctestring, (]."; break;
	case 645: ERRSIN = "Se esperaba un [ identificador, cteentera, ctereal, ctenotacion, ctecaracter, ctestring, (]."; break;
	case 646: ERRSIN = "Se esperaba un operador [ *, /, %, **, +, -, ==, !=, <, <=, >, >=, &&, ||, ;, ,, ), to]."; break;
	case 647: ERRSIN = "Se esperaba un operador [ ==, !=, <, <=, >, >= ] o un [ identificador, cteentera, ctereal, ctenotacion, ctecaracter, ctestring, ( ]."; break;
	case 648: ERRSIN = "Se esperaba un [ identificador, cteentera, ctereal, ctenotacion, ctecaracter, ctestring, ( ]."; break;
	case 649: ERRSIN = "Se esperaba un [ (,  *, /, %, **, +, -, ==, !=, <, <=, >, >=, &&, ||, , , ), to ]."; break;
	case 650: ERRSIN = "Se esperaba un identificador o )."; break;
	case 651: ERRSIN = "Se esperaba , o )."; break;
	case 652: ERRSIN = "Token insesperado, elemento no reconocido por el sintáctico."; break;
	case 800: ERRSIN = "Fin de archivo inesperado"; break;
	}
}

std::vector <Tokenizador> tokensA;
std::vector <MostrarError> errorG;

void TalosV3::Interfaz::AnalizadorSintactico(TalosV3::Interfaz^ form) {
	System::String^ codespace = form->CodeSpace->Text;
	std::stack<int> PilaSintactico;
	errorG.clear(); 
	tokensA.clear();
	cont_cadena = 0;
	index = 0;
	palabraTemp = "";
	form->SintaxisSpace->Clear();
	form->TokenSpace->Clear();
	form->ErrorsSpaces->Clear();
	
	bool esNoTerminal = false, error = false, TerminaTexto = false;
	MostrarError errorcito;

	Tokenizador tokencito = GetNextToken(codespace);
	if (tokencito.edo >= 500) return;

	PilaSintactico.push(1059); // $
	PilaSintactico.push(1); // PROGRAM
	while (PilaSintactico.top() != 1059 && !error) {
		if (tokencito.edo == 132 || tokencito.edo == 131) { //comentarios
			tokencito = GetNextToken(codespace);
			continue;
		}
		if (tokencito.edo == 127 || tokencito.edo == 121 || tokencito.edo == 122) { // # [ ]
			error = true;
			errorcito.edo = 652; // Error de elemento no reconocido
			ErroresSin(652);
			errorcito.Mensaje = ERRSIN;
			errorG.push_back(errorcito);
		}
		if (PilaSintactico.top() == 700) { // Si el tope de la pila es $
			PilaSintactico.pop(); // Sacamos el Vacio
		}
		if (PilaSintactico.top() <= 52) {
			int fila = PilaSintactico.top();
			int col = relacionaTokenMatrizPre(tokencito.edo, palabraTemp);
			if (fila > 0) {
				fila--;
			}

			if (col < 0 || col >= matrizPre[fila].size()) {
				error = true;
				errorcito.edo = 652; // Error de elemento no reconocido
				ErroresSin(652);
				errorcito.Mensaje = ERRSIN;
				errorG.push_back(errorcito);
				break;
			}

			int numprod = matrizPre[fila][col];
			if (numprod >= 1 && numprod <= 109) {
				esNoTerminal = true;

				if (esNoTerminal) {
					PilaSintactico.pop();
					//sacar tope de pila que es la produccion que se va a vaciar

					for (int elemento : producciones[numprod-1])
					{
						PilaSintactico.push(elemento);
					}
				}
			}
			else if (numprod >= 600 && numprod < 700 || numprod == 800) {
				error = true;
				errorcito.edo = numprod;
				ErroresSin(numprod);
				errorcito.Mensaje = ERRSIN;
				errorG.push_back(errorcito); // Agregar el error a la lista de errores
			}
		}
		if (PilaSintactico.top() >= 1000 && PilaSintactico.top() <= 1059) {

			if (PilaSintactico.top() == colPre) {

				int token_id = PilaSintactico.top();
				if (token_id >= 1006 && token_id <= 1011) { // Si es un tipo de dato desde int hasta void
					AccionId2(tokencito.lexema);
				}

				PilaSintactico.pop();
				tokensA.push_back(tokencito); // Agregar el token a la lista de tokens aceptados
				if (cont_cadena+1 == codespace->Length) {
					TerminaTexto = true;
				}
				tokencito = GetNextToken(codespace); // Avanzar al siguiente token
				relacionaTokenMatrizPre(tokencito.edo, palabraTemp);
			}
			else {
				// Error de sintaxis, token inesperado
				ErroresSin(tokencito.edo); // Fin de archivo inesperado
				errorcito.edo = tokencito.edo;
				System::String^ managed_string = gcnew System::String(ERRSIN.c_str());
				errorcito.Mensaje = msclr::interop::marshal_as<string>(managed_string);
				errorG.push_back(errorcito);
				break;
				//return;
			}
		}
	}
	if (PilaSintactico.top() == 1059) {
		relacionaTokenMatrizPre(tokencito.edo, palabraTemp);
		if (PilaSintactico.top() != colPre) { // Si no es EoF
			error = true;
			ErroresSin(508);
			errorcito.edo = 508;
			errorcito.Mensaje = ERRSIN;
			errorG.push_back(errorcito);
		}
		//return;
		//break;
	}
	//Mostrar cosas en la interfaz
	for (Tokenizador token : tokensA) { // lexema, gramema
		System::String^ lexema = gcnew System::String(token.lexema.c_str());
		System::String^ gramema = gcnew System::String(token.gramema.c_str());
		System::String^ lexemaFormato = ("'" + lexema + "'")->PadRight(20);
		System::String^ showT = lexemaFormato + gramema + "\n";
		form->TokenSpace->AppendText(showT);
	}
	if (errorG.empty()) {
		form->SintaxisSpace->SelectionColor = System::Drawing::Color::Green;
		form->SintaxisSpace->AppendText("Análisis sintáctico completado correctamento.\n");
	}
	else {
		form->SintaxisSpace->SelectionColor = System::Drawing::Color::Red;
		form->SintaxisSpace->AppendText("Análisis sintáctico con errores.\n");
	}
	for (MostrarError error : errorG) {
		System::String^ codeError = gcnew System::String(errorcito.edo.ToString());
		System::String^ message = gcnew System::String(errorcito.Mensaje.c_str());
		form->ErrorsSpaces->AppendText("Error: "+ codeError+". "+ message);
	}
}

#pragma endregion



[STAThreadAttribute]
void main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	// Create the main window and run it
	TalosV3::Interfaz form;
	Application::Run(% form);
}

