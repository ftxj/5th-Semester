#ifndef GG_H
#define GG_H
#include <WinSock2.h>
#include <stdio.h>
#include <fstream>
#include <thread>
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include "mainwindow.h"
#include "socketclass.h"
#include "user.h"
#include "datebase.h"

using namespace std;
namespace gg {
const std::string dataAddr = "C:\\Document\\CN\\lab1\\data\\";

const WORD	wVersionRequest = 0x1001;
const int servert_port = 66008;
const int buflen = 255;

}
#endif // GG_H
