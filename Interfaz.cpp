
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
std::string cadenaA, linea, TOKEN = "", lexema_id = "";
std::string TokenTem;
std::string ERR = "", formaPalabraR = "",Palabra = "",ERRSIN = "", palabraTemp = "", ERRSEM = "";
int edo, col,colPre = -1, ap_ini,edoAnterior, longitud;
int estadoLexicoActual = -1; 
char c, analizado;
int cont_cadena = 0, index = 0, cont_direcc = 100, cont_resultado = 1;
bool culmina = false, esReservada = false, accionSemantica = false, esDeclaracion = false;
Simbolos simbolo;

std::unordered_map<std::string, Simbolos> tablaSimbolos;
std::unordered_map<std::string, int> mapaTipos;
std::unordered_map<int, bool> tiposPermitidos;

std::vector<std::string> pilaLexemas;
std::stack<std::string> pilaTipos;
std::stack<std::string> pilaOpr;
std::stack<std::string> pilaOperandos;
std::vector<std::string> ErroresSemanticos;

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
	{4, 2, 3}, // PROGRAM	
	{2, 6}, //PROD1
	{2, 5}, // PROD1
	{2, 15}, //PROD1
	{700},// PROD1
	{3, 1054, 1057, 1058, 1005, 1000}, //DECLARA LIB
	{700}, // DECLARA LIB
	{1047, 18, 1004}, //DECLARA CLASS
	{5, 1054, 14, 1051, 1005, 1002}, //DECLARA CONS
	{700}, // DECLARA CONS
	{6, 1054, 13, 1050, 7, 1001}, //DECLARA VAR
	{8,1005}, // PROD-ID
	{7,1053}, // PROD-ID2
	{700}, // PROD-ID2
	{10,1005}, //PROD-ID3
	{9,1053},//PROD-ID4
	{700}, // PROD-ID4
	{700}, //DECLARA VAR
	{1006}, // TIPO INT
	{1007}, // TIPO FLOAT
	{1008}, // TIPO CHAR
	{1009}, // TIPO STRING
	{1010}, // TIPO BOOLEAN
	{1011}, // TIPO VOID
	{2001,1012}, // VALOR CONS INT
	{2001,1013}, // VALOR CONS FLOAT
	{2001,1014}, // VALOR CONS NOTACION
	{2001,1015}, // VALOR CONS CHAR
	{2001,1016}, // VALOR CONS STRING
	{15, 1048, 18, 6, 1052, 16, 1026, 13, 1051, 1005, 1003}, // DECLARA FUNCT
	{700}, // DECLARA FUNCT
	{17, 13, 1051, 9}, //PARAMETROS
	{700}, // PARAMETROS
	{16, 1053}, //PARAMETROS2
	{700}, // PARAMETROS2
	{18, 1054, 19}, //ESTATUTOS
	{18, 20}, //ESTATUTOS
	{700}, // ESTATUTOS
	{21}, //ESTATUTOS-CP
	{24}, //ESTATUTOS-CP
	{23}, //ESTATUTOS-CP
	{22}, //ESTATUTOS-CP
	{27}, //ESTATUTOS-CP
	{31}, //ESTATUTOS-SP
	{34}, //ESTATUTOS-SP
	{30}, //ESTATUTOS-SP
	{35}, //ESTATUTOS-SP
	{29, 2001,1005}, // EST-ASIG-POST
	{1052, 11, 1026, 1019}, //EST-READ
	{1052, 25, 1026, 1018}, //EST-WRITE
	{36, 1017}, //EST-RETURN
	{26, 36},//PROD-EXPR
	{25, 1053}, //PROD-EXPR2
	{700}, // PROD-EXPR2
	{1005, 28}, //PREINCUARIO
	{1020}, //OPR
	{1021}, // OPR
	{2009,36,2002,1051}, //ID2 '= EXPR'
	{1020}, // ID2
	{1021}, // ID2
	{1056, 2024, 1052, 2008, 2014, 36, 2007, 1026, 1049, 18, 2023, 1024},
	//{1056, 2024, 1052, 2008, 36, 2014, 1026, 2007, 1049, 18, 2023, 1024}, //EST-DO
	//{1056, 1052, 36, 1026, 1049, 18, 1024}, //EST-DO
	{2012, 1044, 33, 32, 18, 1052, 2008, 2010, 2014, 36, 2007, 1026, 1022}, //EST-IF
	{32, 2011, 18, 1052, 2008, 2010, 2014, 36, 2007, 1026, 1042},//PROD-ELSEIF
	{700}, // PROD-ELSEIF
	{18, 2011, 1043}, //PROD-ELSE
	{700}, // PROD-ELSE
	//{1045, 2022, 18, 1052, 2021, 2014, 36, 2007, 1026, 2020, 1023},
	{1045, 2022, 18, 1052, 2008, 2021, 2014, 36, 2007, 1026, 2020, 1023},//EST-WHILE
	{1046, 2019, 18, 1052, 2018, 2017, 36, 1055, 2016, 36, 1026, 2001, 1005, 1025},
	//{1046, 18, 1052, 36, 1055, 36, 1026, 1005, 1025}, //EST-FOR
	{37, 2004,38}, //EXPR
	{36, 2006,1028}, //PROD2
	{2004,700}, // PROD2
	{39, 2003,40}, //EXPR2
	{36, 2005,1029}, //PROD3
	{2003,700}, // PROD3
	{41}, //EXPR3
	{41, 1027, 2014}, //EXPR3
	{42, 43}, //EXPR4
	{43, 48}, //PROD4
	{700}, // PROD4
	{44,2004,46}, //EXPR5
	{43,45}, //PROD5    voy a quitar el 2006
	{2004,700}, // PROD5
	{2006,1036}, //PROD-SIGNO
	{2006,1037}, // PROD-SIGNO
	{700}, // PROD-SIGNO
	{47, 2003,49}, //TERM
	{46, 2005,1038}, //PROD6
	{46, 2005,1039}, // PROD6
	{46, 2005,1040}, // PROD6
	{46, 2005,1041}, // PROD6
	{2003,700}, // PROD6
	{2015, 1030}, //OPREL
	{2015, 1031}, // OPREL
	{2015, 1032}, // OPREL
	{2015, 1033}, // OPREL
	{2015, 1034}, // OPREL
	{2015, 1035}, // OPREL
	{50, 2001,1005},//FACT
	{14}, // FACT
	{2008,1052,36, 2007,1026}, //FACT
	{1052, 51, 1026}, //LLAMADA-F
	{ 700 }, // LLAMADA-F
	{52, 1005}, //PROD-LLAMADA
	{700}, //PROD-LLAMADA
	{51, 1053}, //PROD7
	{ 700 }, // PROD7
	{ 12, 1005 }, //PRDO-ID5
	{11, 1053},//PROD-ID6
	{700}, //PROD-ID6
};

std::string PalabrasReservadas[31] = {"include","lib","endlib","class","endclass","int","float","char","string","bool","void","if","elseif","else","endif","do","enddo","while","endwhile","read","write","def","const","of","dowhile","for","endfor","function","endfunction","return","to"};

int EstadoDiferente[14] = {100,101,102,103,104,109,111,113,116,126,105,106,108,107};

#pragma endregion

#pragma region Estructuras para Cuádruplos

struct Cuadruplo {
	std::string operador;
	std::string op1;
	std::string op2;
	std::string resultado;
	int direccion;
};

std::vector<Cuadruplo> listaCuadruplos;
std::stack<int> pilaSaltos;
int contadorCuadruplos = 0;
std::string varFor_actual = "";

void GenerarCuadruplo(std::string oper, std::string operando1, std::string operando2, std::string res) {
	Cuadruplo cuad;
	cuad.operador = oper;
	cuad.op1 = operando1;
	cuad.op2 = operando2;
	cuad.resultado = res;
	cuad.direccion = contadorCuadruplos;

	listaCuadruplos.push_back(cuad);
	contadorCuadruplos++;

	std::cout << "Cuadruplo [" << cuad.direccion << "]: ("
		<< cuad.operador << ", "
		<< cuad.op1 << ", "
		<< cuad.op2 << ", "
		<< cuad.resultado << ")" << std::endl;
}

void RellenarCuadruplo(int direccion, int valorSalto) {
	if (direccion >= 0 && direccion < listaCuadruplos.size()) {
		listaCuadruplos[direccion].resultado = std::to_string(valorSalto);
		std::cout << "Rellenando cuadruplo [" << direccion << "] con salto a: " << valorSalto << std::endl;
	}
}

void MostrarCuadruplos(TalosV3::Interfaz^ form) {
	//form->CuadruplosSpace->Clear(); // Asume que tienes un TextBox llamado CuadruplosSpace

	//for (const auto& cuad : listaCuadruplos) {
	//	System::String^ linea = "[" + cuad.direccion + "] (" +
	//		gcnew System::String(cuad.operador.c_str()) + ", " +
	//		gcnew System::String(cuad.op1.c_str()) + ", " +
	//		gcnew System::String(cuad.op2.c_str()) + ", " +
	//		gcnew System::String(cuad.resultado.c_str()) + ")\n";

	//form->CuadruplosSpace->AppendText(linea);
	 
	std::cout << "\n========================================" << std::endl;
	std::cout << "       CUÁDRUPLOS GENERADOS" << std::endl;
	std::cout << "========================================" << std::endl;

	if (listaCuadruplos.empty()) {
		std::cout << "No se generaron cuádruplos." << std::endl;
	}
	else {
		for (const auto& cuad : listaCuadruplos) {
			std::cout << "[" << cuad.direccion << "] ("
				<< cuad.operador << ", "
				<< cuad.op1 << ", "
				<< cuad.op2 << ", "
				<< cuad.resultado << ")" << std::endl;
		}
	}

	std::cout << "========================================\n" << std::endl;

//	}
}

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

enum ReglasTipos {
	int_int = 10,
	int_float = 11,
	float_int = 12,
	float_float = 13,
	forzarPermitido = 50,
	noPermitido = 99
};

void iniciarReglas() {
	mapaTipos["int_int"] = ReglasTipos::int_int;
	mapaTipos["int_float"] = ReglasTipos::int_float;
	//mapaTipos["int_char"] = ReglasTipos::noPermitido;
	//mapaTipos["int_string"] = ReglasTipos::noPermitido;
	//mapaTipos["int_bool"] = ReglasTipos::noPermitido;
	mapaTipos["float_int"] = ReglasTipos::float_int;
	mapaTipos["float_float"] = ReglasTipos::float_float;
	//mapaTipos["float_char"] = ReglasTipos::noPermitido;
	//mapaTipos["float_string"] = ReglasTipos::noPermitido;
	/*mapaTipos["float_bool"] = ReglasTipos::noPermitido;
	mapaTipos["char_int"] = ReglasTipos::noPermitido;
	mapaTipos["char_float"] = ReglasTipos::noPermitido;
	mapaTipos["char_char"] = ReglasTipos::noPermitido;
	mapaTipos["char_string"] = ReglasTipos::noPermitido;
	mapaTipos["char_bool"] = ReglasTipos::noPermitido;
	mapaTipos["string_int"] = ReglasTipos::noPermitido;
	mapaTipos["string_float"] = ReglasTipos::noPermitido;
	mapaTipos["string_char"] = ReglasTipos::noPermitido;
	mapaTipos["string_string"] = ReglasTipos::noPermitido;
	mapaTipos["string_bool"] = ReglasTipos::noPermitido;
	mapaTipos["bool_int"] = ReglasTipos::noPermitido;
	mapaTipos["bool_float"] = ReglasTipos::noPermitido;
	mapaTipos["bool_char"] = ReglasTipos::noPermitido;
	mapaTipos["bool_string"] = ReglasTipos::noPermitido;
	mapaTipos["bool_bool"] = ReglasTipos::noPermitido; */

	tiposPermitidos[ReglasTipos::int_int] = true;
	tiposPermitidos[ReglasTipos::int_float] = true;
	tiposPermitidos[ReglasTipos::float_int] = true;
	tiposPermitidos[ReglasTipos::float_float] = true;
	//AQUI PODEMOS FORZAR OTRAS REGLAS EN CASO DE SER NECESARIO
	tiposPermitidos[ReglasTipos::forzarPermitido] = true;
	tiposPermitidos[ReglasTipos::noPermitido] = false;

}

int compTipos(std::string& tipo1, std::string& tipo2) {
	std::string regla = tipo1 + "_" + tipo2; // Contruimos una regla con los tipos que nos envien de donde se llame la funcion

	//Vamos a verificar si esta regla existe en el mapa de tipos
	if (mapaTipos.count(regla)) {
		return mapaTipos.at(regla); // Si existe retornamos el valor asociado a esa regla
	}
		return ReglasTipos::noPermitido; // Si no existe retornamos que no es permitido
}

bool esTipoPermitido(int regla) { // El parametro que le vamos a mandar es el de la regla que nos retorno la funcion compTipos
	if (tiposPermitidos.count(regla)) {
		return tiposPermitidos.at(regla); // Retornamos si es permitido o no
	}
	return false; // Si no existe la regla retornamos false
}

string TipoResultante(int numReglaTipo, std::string& opr) {
	std::cout << numReglaTipo << std::endl;
	if (numReglaTipo == ReglasTipos::int_int) { // Verifica que ambos tipos sean enteros
		if(opr == "+" || opr == "-" || opr == "*")
			return "int";
		else if (opr == "/") // En la division de enteros el resultado es float
			return "float";
	}
	else if (numReglaTipo == ReglasTipos::int_float || numReglaTipo == ReglasTipos::float_int || numReglaTipo == ReglasTipos::float_float) {
		if (opr == "+" || opr == "-" || opr == "*" || opr == "/")
			return "float"; // Si alguno de los dos es float el resultado es float
	}
	else if (numReglaTipo == ReglasTipos::noPermitido) {
		if(opr == "+" || opr == "-" || opr == "*" || opr == "/")
			return "float"; // Por default retornamos float en caso de error que seria un parche para seguir con la compilacion
	}

	return "float"; // Por default retornamos float en caso de error que seria un parche para seguir con la compilacion
}

void VaciarStack() {
	while (!pilaTipos.empty()) {
		pilaTipos.pop();
	}
	while (!pilaOpr.empty()) {
		pilaOpr.pop();
	}
	while (!pilaOperandos.empty()) {
		pilaOperandos.pop();
	}
}

#pragma region Funciones de Impresión de Pilas

void ImprimirStack(std::stack<std::string> pila) {
	std::cout << "Pila (Top -> Bottom): [";
	while (!pila.empty()) {
		std::cout << pila.top();
		pila.pop();
		if (!pila.empty()) {
			std::cout << ", ";
		}
	}
	std::cout << "]\n";
}

void ImprimirPilaSaltos(std::stack<int> pila) {
	std::cout << "Pila Saltos (Top -> Bottom): [";
	while (!pila.empty()) {
		std::cout << pila.top();
		pila.pop();
		if (!pila.empty()) {
			std::cout << ", ";
		}
	}
	std::cout << "]\n";
}

void ImprimirEstadoPilas() {
	std::cout << "\n========== ESTADO DE PILAS ==========" << std::endl;

	// Imprimir Pila de Operandos
	std::cout << "PILA OPERANDOS: ";
	if (pilaOperandos.empty()) {
		std::cout << "[VACIA]" << std::endl;
	}
	else {
		ImprimirStack(pilaOperandos);
	}

	// Imprimir Pila de Operadores
	std::cout << "PILA OPERADORES: ";
	if (pilaOpr.empty()) {
		std::cout << "[VACIA]" << std::endl;
	}
	else {
		ImprimirStack(pilaOpr);
	}

	// Imprimir Pila de Tipos
	//std::cout << "PILA TIPOS: ";
	//if (pilaTipos.empty()) {
	//	std::cout << "[VACÍA]" << std::endl;
	//}
	//else {
	//	ImprimirStack(pilaTipos);
	//}

	// Imprimir Pila de Saltos
	std::cout << "PILA SALTOS: ";
	if (pilaSaltos.empty()) {
		std::cout << "[VACIA]" << std::endl;
	}
	else {
		ImprimirPilaSaltos(pilaSaltos);
	}

	std::cout << "====================================\n" << std::endl;
}

#pragma endregion


#pragma endregion

#pragma region Léxico
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

				if (!esReservada && !Palabra.empty()) {
					edo = 101; // Si no es una palabra reservada, se considera un identificador
					Token(edo); // Es para enviar el token como identificador
					token.edo = edo;
					System::String^ lex = "";
					for (int i = ap_ini; i < index; ++i)
						lex += codespace[i];
					lex = lex->Trim();
					token.lexema = msclr::interop::marshal_as<string>(lex);
					Token(edo);
					token.gramema = TOKEN;
					palabraTemp = Palabra;
					Palabra = "";
					return token;
				}

			}
			else {
				Token(edo); // estado de aceptación, entera, flotante				
				token.edo = edo;
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

#pragma region Semántico
void AccionId1(const std::string& lexema) {
	if (tablaSimbolos.count(lexema)) { // El identificador ya existe en la tabla de símbolos
		ERRSEM = "Error Semantico: Duplicidad de variable: '" + lexema + "' ya definida.";
		std::cout << "Error Semantico: " << ERRSEM << std::endl;
		ErroresSemanticos.push_back(ERRSEM);
	}
	else
		pilaLexemas.push_back(lexema);
} // def x,f,c,v of int

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

void AccionConst1(const std::string& lexema) {
	if (tablaSimbolos.count(lexema)) { // La constante ya existe en la tabla de símbolos
		ERRSEM = "Constante: ' " + lexema + "' ya definida.";
		std::cout << "Error Semantico: " << ERRSEM << std::endl;
		ErroresSemanticos.push_back(ERRSEM);
	}
	else
		pilaLexemas.push_back(lexema);
}

#pragma endregion

#pragma region Acciones Semánticas

void accionesSemanticas(int produccion, std::string lex) {
	std::cout << "\n>>> ACCIÓN " << produccion << " <<<" << std::endl;

	switch (produccion) {

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2001: PUSH operando a pila_operandos
	// Usada en: FACT → id | cte_int | cte_real | cte_char | cte_string
	// Propósito: Insertar variables y constantes en la pila de operandos
	// ═════════════════════════════════════════════════════════════════
	case 2001: {
		std::cout << "→ PUSH operando: " << lex << std::endl;

		// Determinar tipo según estado léxico y agregar a pilas
		if (estadoLexicoActual == 101) {
			// Identificador - verificar en tabla de símbolos
			if (tablaSimbolos.count(lex)) {
				const Simbolos& simbolo = tablaSimbolos.at(lex);
				pilaTipos.push(simbolo.Tipo);
				pilaOperandos.push(lex);
				std::cout << "  Variable: " << lex << " (" << simbolo.Tipo << ")" << std::endl;
			}
			else {
				// Variable no declarada - error semántico
				pilaLexemas.push_back(lex);
				AccionId2("float");
				ERRSEM = "Error Semantico: Variable '" + lex + "' no definida";
				pilaTipos.push("float");
				pilaOperandos.push(lex);
				ErroresSemanticos.push_back(ERRSEM);
				std::cout << "  " << ERRSEM << std::endl;
			}
		}
		else if (estadoLexicoActual == 102) {
			// Constante entera
			pilaTipos.push("int");
			pilaOperandos.push(lex);
			std::cout << "  Cte entera: " << lex << std::endl;
		}
		else if (estadoLexicoActual == 103 || estadoLexicoActual == 104) {
			// Constante real o notación científica
			pilaTipos.push("float");
			pilaOperandos.push(lex);
			std::cout << "  Cte real: " << lex << std::endl;
		}
		else if (estadoLexicoActual == 125) {
			// Constante caracter
			pilaTipos.push("char");
			pilaOperandos.push(lex);
			std::cout << "  Cte char: " << lex << std::endl;
		}
		else if (estadoLexicoActual == 126) {
			// Constante string
			pilaTipos.push("string");
			pilaOperandos.push(lex);
			std::cout << "  Cte string: " << lex << std::endl;
		}
		else {
			// Token inesperado - asumir float
			std::cout << "  Token inesperado (estado " << estadoLexicoActual << ")" << std::endl;
			pilaTipos.push("float");
			pilaOperandos.push(lex);
		}

		ImprimirEstadoPilas();
		break;
	}

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2002: PUSH operador de asignación '='
	// Usada en: ID2 → = EXPR
	// ═════════════════════════════════════════════════════════════════
	case 2002:
		std::cout << "→ PUSH operador '='" << std::endl;
		pilaOpr.push(lex);
		ImprimirEstadoPilas();
		break;

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2003: Generar cuádruplos para operadores multiplicativos
	// Usada en: TERM → TERM (*|/|%|**) FACT
	// Genera: (oper, op1, op2, R)
	// Para generar cuadruplo R con * / % **
	// ═════════════════════════════════════════════════════════════════ 
	case 2003: {
		std::cout << "→ Generar cuádruplo: *, /, %, **" << std::endl;

		// Procesar todos los operadores multiplicativos pendientes
		while (!pilaOpr.empty() && pilaOpr.top() != "MFF") {
			std::string oper = pilaOpr.top();

			if (oper == "*" || oper == "/" || oper == "%" || oper == "**") {
				pilaOpr.pop();

				if (pilaTipos.size() < 2 || pilaOperandos.size() < 2) {
					std::cout << "  Error: Operandos insuficientes" << std::endl;
					break;
				}

				// Extraer operandos (op2 primero, luego op1)
				std::string tipo2 = pilaTipos.top(); pilaTipos.pop();
				std::string op2 = pilaOperandos.top(); pilaOperandos.pop();
				std::string tipo1 = pilaTipos.top(); pilaTipos.pop();
				std::string op1 = pilaOperandos.top(); pilaOperandos.pop();

				// Verificar compatibilidad y generar cuádruplo
				int regla = compTipos(tipo1, tipo2);
				if (esTipoPermitido(regla)) {
					std::string resultadoTipo = TipoResultante(regla, oper);
					pilaTipos.push(resultadoTipo);
					std::string R = "R" + std::to_string(cont_resultado++);
					pilaOperandos.push(R);
					GenerarCuadruplo(oper, op1, op2, R);
				}
				else {
					pilaTipos.push("float");
					std::string R = "R" + std::to_string(cont_resultado++);
					pilaOperandos.push(R);
					ERRSEM = "Error semantico: Operacion '" + oper + "' entre tipos incompatibles";
					ErroresSemanticos.push_back(ERRSEM);
					std::cout << "  " << ERRSEM << std::endl;
					GenerarCuadruplo(oper, op1, op2, R);
				}
			}
			else {
				break;
			}
		}
		ImprimirEstadoPilas();
		break;
	}

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2004: Generar cuádruplos para operadores aditivos
	// Usada en: EXPR2 → EXPR2 (+|-|||) TERM
	// Genera: (oper, op1, op2, R)
	// Generamos cuadruplo R de + - ||
	// ═════════════════════════════════════════════════════════════════
	case 2004: {
		std::cout << "→ Generar cuádruplo: +, -, ||" << std::endl;

		// Procesar todos los operadores aditivos pendientes
		while (!pilaOpr.empty() && pilaOpr.top() != "MFF") {
			std::string oper = pilaOpr.top();

			if (oper == "+" || oper == "-" || oper == "||") {
				pilaOpr.pop();

				if (pilaTipos.size() < 2 || pilaOperandos.size() < 2) {
					std::cout << "  Error: Operandos insuficientes" << std::endl;
					break;
				}

				std::string tipo2 = pilaTipos.top(); pilaTipos.pop();
				std::string op2 = pilaOperandos.top(); pilaOperandos.pop();
				std::string tipo1 = pilaTipos.top(); pilaTipos.pop();
				std::string op1 = pilaOperandos.top(); pilaOperandos.pop();

				int regla = compTipos(tipo1, tipo2);
				if (esTipoPermitido(regla)) {
					std::string resultadoTipo = TipoResultante(regla, oper);
					pilaTipos.push(resultadoTipo);
					std::string R = "R" + std::to_string(cont_resultado++);
					pilaOperandos.push(R);
					GenerarCuadruplo(oper, op1, op2, R);
				}
				else {
					pilaTipos.push("float");
					std::string R = "R" + std::to_string(cont_resultado++);
					pilaOperandos.push(R);
					ERRSEM = "Error semantico: Operacion '" + oper + "' entre tipos incompatibles";
					ErroresSemanticos.push_back(ERRSEM);
					std::cout << "  " << ERRSEM << std::endl;
					GenerarCuadruplo(oper, op1, op2, R);
				}
			}
			else {
				break;
			}
		}
		ImprimirEstadoPilas();
		break;
	}

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2005: PUSH operador multiplicativo
	// Usada en: PROD6 → *|/|%|**
	// ═════════════════════════════════════════════════════════════════
	case 2005:
		std::cout << "→ PUSH operador: " << lex << std::endl;
		pilaOpr.push(lex);
		ImprimirEstadoPilas();
		break;

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2006: PUSH operador aditivo
	// Usada en: PROD2/PROD3 → +|-|||
	// ═════════════════════════════════════════════════════════════════
	case 2006:
		std::cout << "→ PUSH operador: " << lex << std::endl;
		pilaOpr.push(lex);
		ImprimirEstadoPilas();
		break;

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2007: Insertar Marca de Fondo Falso (MFF)
	// Usada en: FACT → ( EXPR ) y condiciones de estructuras
	// Propósito: Delimitar alcance de operadores
	// ═════════════════════════════════════════════════════════════════
	case 2007:
		std::cout << "→ PUSH MFF" << std::endl;
		pilaOpr.push("MFF");
		ImprimirEstadoPilas();
		break;

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2008: Eliminar Marca de Fondo Falso
	// Usada en: Cierre de paréntesis y fin de condiciones
	// ═════════════════════════════════════════════════════════════════
	case 2008:
		std::cout << "→ POP MFF" << std::endl;
		if (!pilaOpr.empty() && pilaOpr.top() == "MFF") {
			pilaOpr.pop();
		}
		ImprimirEstadoPilas();
		break;

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2009: Generar cuádruplo de asignación
	// Usada en: ID2 → = EXPR
	// Genera: (=, variable_destino, , resultado_expresión)
	// ═════════════════════════════════════════════════════════════════
	case 2009: {
		std::cout << "→ Generar asignación" << std::endl;

		if (pilaTipos.size() < 2 || pilaOperandos.size() < 2) {
			std::cout << "  Error: Operandos insuficientes" << std::endl;
			break;
		}

		// Extraer expresión (lado derecho)
		std::string tipo1 = pilaTipos.top(); pilaTipos.pop();
		std::string op1 = pilaOperandos.top(); pilaOperandos.pop();

		// Extraer variable (lado izquierdo)
		std::string tipo2 = pilaTipos.top(); pilaTipos.pop();
		std::string op2 = pilaOperandos.top(); pilaOperandos.pop();

		// Verificar compatibilidad de tipos
		int regla = compTipos(tipo2, tipo1);
		if (tipo2 == tipo1 || esTipoPermitido(regla)) {
			if (!pilaOpr.empty()) {
				pilaOpr.pop(); // Sacar '='
			}
			// Orden: (=, destino, , origen)
			GenerarCuadruplo("=", op2, "", op1);
		}
		else {
			ERRSEM = "Error semantico: Tipo incompatible en asignación";
			ErroresSemanticos.push_back(ERRSEM);
			std::cout << "  " << ERRSEM << std::endl;
			if (!pilaOpr.empty()) {
				pilaOpr.pop();
			}
		}
		ImprimirEstadoPilas();
		break;
	}


	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2010: GotoF del IF
	// Usada en: EST-IF → if ( EXPR )
	// Genera: (GotoF, condicion, , ?) - pendiente
	// Si condicion es FALSE → Salta al siguiente bloque
	// ═════════════════════════════════════════════════════════════════
	case 2010: {
		std::cout << "→ IF: SF (siguiente bloque si FALSE)" << std::endl;

		if (!pilaOperandos.empty()) {
			std::string condicion = pilaOperandos.top();
			pilaOperandos.pop();

			if (!pilaTipos.empty()) {
				pilaTipos.pop();
			}

			GenerarCuadruplo("SF", condicion, "", "?");
			pilaSaltos.push(contadorCuadruplos - 1);
			std::cout << "  SF en: [" << (contadorCuadruplos - 1) << "]" << std::endl;
		}

		ImprimirEstadoPilas();
		break;
	}

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2011: Goto del IF (saltar al final)
	// Usada en: EST-IF → después de bloque if/elseif
	// Genera: (Goto, , , ?) - pendiente
	// Rellena: GotoF anterior con dirección actual
	// ═════════════════════════════════════════════════════════════════
	case 2011: {
		std::cout << "→ IF: SI al final" << std::endl;

		// Generar Goto incondicional
		GenerarCuadruplo("SI", "", "", "?");
		int dirGoto = contadorCuadruplos - 1;

		// Rellenar GotoF anterior
		if (!pilaSaltos.empty()) {
			int dirGotoF = pilaSaltos.top();
			pilaSaltos.pop();
			RellenarCuadruplo(dirGotoF, contadorCuadruplos);
			std::cout << "  Relleno SI[" << dirGotoF << "] -> " << contadorCuadruplos << std::endl;
		}

		// Guardar nuevo Goto para rellenar al ENDIF
		pilaSaltos.push(dirGoto);
		std::cout << "  SI en: [" << dirGoto << "]" << std::endl;

		ImprimirEstadoPilas();
		break;
	}

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2012: Rellenar todos los Goto del IF
	// Usada en: EST-IF → endif
	// Rellena: Todos los Goto pendientes con dirección actual
	// ═════════════════════════════════════════════════════════════════
	case 2012: {
		std::cout << "→ IF: Rellenar todos los SI (ENDIF)" << std::endl;

		// Rellenar todos los saltos pendientes
		while (!pilaSaltos.empty()) {
			int dirSalto = pilaSaltos.top();
			pilaSaltos.pop();
			RellenarCuadruplo(dirSalto, contadorCuadruplos);
			std::cout << "  Relleno [" << dirSalto << "] -> " << contadorCuadruplos << std::endl;
		}

		ImprimirEstadoPilas();
		break;
	}

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2014: Generar cuádruplos para operadores relacionales
	// Usada en: EXPR3 → EXPR3 (<|<=|>|>=|==|!=) EXPR2
	// Genera: (oper, op1, op2, R) donde R es tipo 'bool'
	// ═════════════════════════════════════════════════════════════════
	case 2014: {
		std::cout << "→ Generar cuádruplo relacional" << std::endl;

		while (!pilaOpr.empty() && pilaOpr.top() != "MFF") {
			std::string oper = pilaOpr.top();

			if (oper == ">" || oper == "<" || oper == "==" ||
				oper == "!=" || oper == ">=" || oper == "<=") {
				pilaOpr.pop();

				if (pilaTipos.size() < 2 || pilaOperandos.size() < 2) {
					std::cout << "  Error: Operandos insuficientes" << std::endl;
					break;
				}

				std::string tipo2 = pilaTipos.top(); pilaTipos.pop();
				std::string op2 = pilaOperandos.top(); pilaOperandos.pop();
				std::string tipo1 = pilaTipos.top(); pilaTipos.pop();
				std::string op1 = pilaOperandos.top(); pilaOperandos.pop();

				// Resultado siempre es bool
				pilaTipos.push("bool");
				std::string R = "R" + std::to_string(cont_resultado++);
				pilaOperandos.push(R);
				GenerarCuadruplo(oper, op1, op2, R);
			}
			else {
				break;
			}
		}
		ImprimirEstadoPilas();
		break;
	}

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2015: PUSH operador relacional
	// Usada en: OPREL → ==|!=|<|<=|>|>=
	// ═════════════════════════════════════════════════════════════════
	case 2015:
		std::cout << "→ PUSH operador relacional: " << lex << std::endl;
		pilaOpr.push(lex);
		ImprimirEstadoPilas();
		break;

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2016: Inicialización del FOR
	// Usada en: EST-FOR → for id ( EXPR
	// Genera: (=, variable_for, , valor_inicial)
	// Guarda: inicio_ciclo en pila_saltos
	// Re-inserta: variable_for en pilas para comparación posterior
	// ═════════════════════════════════════════════════════════════════
	case 2016: {
		std::cout << "→ FOR: Inicialización" << std::endl;

		if (pilaTipos.size() < 2 || pilaOperandos.size() < 2) {
			std::cout << "  Error: Operandos insuficientes" << std::endl;
			break;
		}

		// Extraer valor inicial
		std::string tipo1 = pilaTipos.top(); pilaTipos.pop();
		std::string op1 = pilaOperandos.top(); pilaOperandos.pop();

		// Extraer variable del FOR
		std::string tipo2 = pilaTipos.top(); pilaTipos.pop();
		std::string varFor = pilaOperandos.top(); pilaOperandos.pop();

		varFor_actual = varFor;

		// Generar cuádruplo: (=, destino, , origen)
		GenerarCuadruplo("=", varFor, "", op1);

		// Guardar inicio del ciclo
		pilaSaltos.push(contadorCuadruplos);
		std::cout << "  Inicio ciclo: [" << contadorCuadruplos << "]" << std::endl;

		// Re-insertar variable para comparación
		if (tablaSimbolos.count(varFor)) {
			pilaTipos.push(tablaSimbolos.at(varFor).Tipo);
			pilaOperandos.push(varFor);
		}

		ImprimirEstadoPilas();
		break;
	}

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2017: Condición de salida del FOR
	// Usada en: EST-FOR → for id ( EXPR to EXPR
	// Genera: (>, variable_for, valor_final, R)
	// Operador '>': Sale del ciclo cuando variable_for > valor_final
	// ═════════════════════════════════════════════════════════════════
	case 2017: {
		std::cout << "→ FOR: Condición (varFor > limite)" << std::endl;

		if (pilaTipos.size() < 2 || pilaOperandos.size() < 2) {
			std::cout << "  Error: Operandos insuficientes" << std::endl;
			break;
		}

		// Extraer límite del TO
		std::string tipo2 = pilaTipos.top(); pilaTipos.pop();
		std::string op2 = pilaOperandos.top(); pilaOperandos.pop();

		// Extraer variable del FOR
		std::string tipo1 = pilaTipos.top(); pilaTipos.pop();
		std::string op1 = pilaOperandos.top(); pilaOperandos.pop();

		// Generar comparación con '>'
		std::string R = "R" + std::to_string(cont_resultado++);
		pilaTipos.push("bool");
		pilaOperandos.push(R);
		GenerarCuadruplo(">", op1, op2, R);

		ImprimirEstadoPilas();
		break;
	}

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2018: GotoV del FOR (salida)
	// Usada en: EST-FOR → después de condición
	// Genera: (GotoV, condicion, , ?) - pendiente de rellenar
	// Si condicion es TRUE → Sale del FOR
	// ═════════════════════════════════════════════════════════════════
	case 2018: {
		std::cout << "→ FOR: SV (salida si TRUE)" << std::endl;

		if (!pilaOperandos.empty()) {
			std::string condicion = pilaOperandos.top();
			pilaOperandos.pop();

			if (!pilaTipos.empty()) {
				pilaTipos.pop();
			}

			GenerarCuadruplo("SV", condicion, "", "?");
			pilaSaltos.push(contadorCuadruplos - 1);
			std::cout << " SV en: [" << (contadorCuadruplos - 1) << "]" << std::endl;
		}

		ImprimirEstadoPilas();
		break;
	}

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2019: Cierre del FOR
	// Usada en: EST-FOR → endfor
	// Genera: (SI, , , inicio_ciclo)
	// Rellena: SV anterior con dirección de salida
	// ═════════════════════════════════════════════════════════════════
	case 2019: {
		std::cout << "→ FOR: Cierre (SI inicio)" << std::endl;

		if (pilaSaltos.size() >= 2) {
			// Sacar dirección del SV
			int dirGotoV = pilaSaltos.top();
			pilaSaltos.pop();

			// Sacar dirección del inicio
			int dirInicio = pilaSaltos.top();
			pilaSaltos.pop();

			// Generar SI al inicio
			GenerarCuadruplo("SI", "", "", std::to_string(dirInicio));

			// Rellenar SV
			RellenarCuadruplo(dirGotoV, contadorCuadruplos);
			std::cout << "  Relleno SV[" << dirGotoV << "] -> " << contadorCuadruplos << std::endl;
		}

		varFor_actual = "";
		ImprimirEstadoPilas();
		break;
	}

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2020: Guardar inicio del WHILE
	// Usada en: EST-WHILE → while (
	// Guarda: posición actual en pila_saltos
	// ═════════════════════════════════════════════════════════════════
	case 2020: {
		std::cout << "→ WHILE: Guardar inicio" << std::endl;
		pilaSaltos.push(contadorCuadruplos);
		std::cout << "  Inicio: [" << contadorCuadruplos << "]" << std::endl;
		ImprimirEstadoPilas();
		break;
	}

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2021: GotoF del WHILE
	// Usada en: EST-WHILE → while ( EXPR )
	// Genera: (GotoF, condicion, , ?) - pendiente
	// Si condicion es FALSE → Sale del WHILE
	// ═════════════════════════════════════════════════════════════════
	case 2021: {
		std::cout << "→ WHILE: SF (salida si FALSE)" << std::endl;

		if (!pilaOperandos.empty()) {
			std::string condicion = pilaOperandos.top();
			pilaOperandos.pop();

			if (!pilaTipos.empty()) {
				pilaTipos.pop();
			}

			GenerarCuadruplo("SF", condicion, "", "?");
			pilaSaltos.push(contadorCuadruplos - 1);
			std::cout << "  SF en: [" << (contadorCuadruplos - 1) << "]" << std::endl;
		}

		ImprimirEstadoPilas();
		break;
	}

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2022: Cierre del WHILE
	// Usada en: EST-WHILE → endwhile
	// Genera: (Goto, , , inicio)
	// Rellena: GotoF con dirección de salida
	// ═════════════════════════════════════════════════════════════════
	case 2022: {
		std::cout << "→ WHILE: Cierre (SI inicio)" << std::endl;

		if (pilaSaltos.size() >= 2) {
			int dirGotoF = pilaSaltos.top();
			pilaSaltos.pop();
			int dirInicio = pilaSaltos.top();
			pilaSaltos.pop();

			GenerarCuadruplo("SI", "", "", std::to_string(dirInicio));
			RellenarCuadruplo(dirGotoF, contadorCuadruplos);
			std::cout << "  Relleno SF[" << dirGotoF << "] -> " << contadorCuadruplos << std::endl;
		}

		ImprimirEstadoPilas();
		break;
	}

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2023: Guardar inicio del DO
	// Usada en: EST-DO → do ESTATUTOS
	// Guarda: posición actual en pila_saltos
	// ═════════════════════════════════════════════════════════════════
	case 2023: {
		std::cout << "→ DO: Guardar inicio" << std::endl;
		pilaSaltos.push(contadorCuadruplos);
		std::cout << "  Inicio: [" << contadorCuadruplos << "]" << std::endl;
		ImprimirEstadoPilas();
		break;
	}

	// ═════════════════════════════════════════════════════════════════
	// ACCIÓN 2024: GotoV del DO-WHILE
	// Usada en: EST-DO → dowhile ( EXPR )
	// Genera: (GotoV, condicion, , inicio)
	// Si condicion es TRUE → Repite el DO
	// ═════════════════════════════════════════════════════════════════
	case 2024: {
		std::cout << "→ DO: SV (repetir si TRUE)" << std::endl;

		if (!pilaOperandos.empty()) {
			std::string condicion = pilaOperandos.top();
			pilaOperandos.pop();

			if (!pilaTipos.empty()) {
				pilaTipos.pop();
			}

			if (!pilaSaltos.empty()) {
				int dirInicio = pilaSaltos.top();
				pilaSaltos.pop();

				GenerarCuadruplo("SV", condicion, "", std::to_string(dirInicio));
				std::cout << "  SV -> [" << dirInicio << "]" << std::endl;
			}
		}

		ImprimirEstadoPilas();
		break;
	}

	

	default:
		std::cout << "Acción no reconocida: " << produccion << std::endl;
		break;
	}
}

#pragma endregion

#pragma region Sintáctico
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
	VaciarStack();

	// **INICIALIZAR CONTADORES Y LIMPIAR ESTRUCTURAS DE CUÁDRUPLOS**
	contadorCuadruplos = 0;
	cont_resultado = 1;
	listaCuadruplos.clear();
	while (!pilaSaltos.empty()) pilaSaltos.pop();

	bool esConstante = false;
	int token_id;
	std::string lexConst;
	errorG.clear();
	tokensA.clear();
	cont_cadena = 0;
	index = 0;
	palabraTemp = "";
	form->SintaxisSpace->Clear();
	form->TokenSpace->Clear();
	form->ErrorsSpaces->Clear();
	tablaSimbolos.clear();
	ErroresSemanticos.clear();

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

					for (int elemento : producciones[numprod - 1])
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
		else if (PilaSintactico.top() >= 1000 && PilaSintactico.top() <= 1059) {

			if (PilaSintactico.top() == colPre) {

				token_id = PilaSintactico.top();

				estadoLexicoActual = tokencito.edo;

				if (token_id == 1001) // si es la palabra def  || token_id == 1002
					esDeclaracion = true;
				if (token_id == 1002) { // si es la palabra const
					esConstante = true;
				}
				if (token_id == 1005) { // Si es un identificador
					if (esDeclaracion)
						AccionId1(tokencito.lexema);
					else if (esConstante) {
						AccionConst1(tokencito.lexema);
						lexConst = tokencito.lexema;
					}
				}
				if (token_id >= 1006 && token_id <= 1011) { // Si es un tipo de dato desde int hasta void

					AccionId2(tokencito.lexema);
					esDeclaracion = false;
				}
				TokenTem = tokencito.lexema;
				PilaSintactico.pop();
				tokensA.push_back(tokencito); // Agregar el token a la lista de tokens aceptados
				if (cont_cadena + 1 == codespace->Length) {
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
		else if (PilaSintactico.top() >= 2001 && PilaSintactico.top() <= 2024) {
			int numP = PilaSintactico.top();
			PilaSintactico.pop();
			//estadoLexicoActual = tokencito.edo;  

			if (esConstante && numP == 2001) {
				if (token_id >= 1012 && token_id <= 1016) { // Valor de las constantes
					if (token_id == 1012) {
						//tokencito.lexema = "int";
						AccionId2("int");
						accionesSemanticas(numP, lexConst);
						esConstante = false;
						continue;
					}
					else if (token_id == 1013 || token_id == 1014) { // real o 'notacion'
						//tokencito.lexema = "float";
						AccionId2("float");
						accionesSemanticas(numP, lexConst);
						esConstante = false;
						continue;
					}
					else if (token_id == 1015) {
						//tokencito.lexema = "char";
						AccionId2("char");
						accionesSemanticas(numP, lexConst);
						esConstante = false;
						continue;
					}
					else if (token_id == 1016) {
						//tokencito.lexema = "string";
						AccionId2("string");
						accionesSemanticas(numP, lexConst);
						esConstante = false;
						continue;
					}

				}
			}
			accionesSemanticas(numP, TokenTem);

		}
	}
	MostrarCuadruplos(form);

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
		form->SintaxisSpace->AppendText("Análisis sintáctico correcto.\n");
	}
	else {
		form->SintaxisSpace->SelectionColor = System::Drawing::Color::Red;
		form->SintaxisSpace->AppendText("Análisis sintáctico con errores.\n");
	}
	for (MostrarError error : errorG) {
		System::String^ codeError = gcnew System::String(errorcito.edo.ToString());
		System::String^ message = gcnew System::String(errorcito.Mensaje.c_str());
		form->ErrorsSpaces->AppendText("Error: " + codeError + ". " + message);
	}
	for (int i = 0; i < ErroresSemanticos.size(); i++) {
		System::String^ ErrorSemantico = gcnew System::String(ErroresSemanticos[i].c_str());
		form->ErrorsSpaces->AppendText(ErrorSemantico + "\n");
	}
}

#pragma endregion


[STAThreadAttribute]
void main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	// Create the main window and run it
	iniciarReglas();
	TalosV3::Interfaz form;
	Application::Run(% form);
	
}

