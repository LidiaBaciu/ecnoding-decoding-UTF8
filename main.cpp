/* 
 * File:   main.cpp
 * Author: Lidia
 *
 * Created on November 9, 2017, 10:26 AM
 */
//encoder 4byts doesnt work well ?

#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <math.h>
#include <iostream>
#include <string.h>

using namespace std;

unsigned long binaryStringToInt( char* binary_string){
    
    int power = 0;
    long value = 0;
    
    for( int i = strlen(binary_string) - 1; i >= 0; i--){
        
        if(binary_string[i] == '1'){
            value += pow(2, power);
        }
        power++;
        
    }
    
    return value;
    
}


void hexToBin (char *bits, unsigned long value) {
    int i=0;
    char reverse_bits[4];
    
    while (value > 0){
        int r = value % 2;
        if (r == 1){
            reverse_bits[i] = '1';
        }
        else reverse_bits[i] = '0';
        
        i++;
        value /= 2;
    }
    
    while (i <= 3){
        reverse_bits[i] = '0';
        i++;
    }
    
    for(i=0; i<=3; i++){
        bits[i] = reverse_bits[3-i];
    }
}


int main(int argc, char** argv) {

    /// ################  Encoder  ################
    
    string codePoint_string;
    unsigned long codePoint = 0;
    string encoded_hex;
    stringstream sse;
    
    
    cout << "Enter number for encoding (hex code point): ";//FARA SPATIU
    getline(cin, codePoint_string, '\n');
    
    char codePoint_binary[33] = "";

    for (long i=0; i<codePoint_string.size(); i++){
        
        if (codePoint_string[i] >= '0' && codePoint_string[i] <='9'){
            codePoint = codePoint_string[i] - '0';
            char bits[5] = "";
            hexToBin(bits, codePoint);
            //cout<< bits << endl;
            strcat(codePoint_binary, bits);
        }
        
        if (codePoint_string[i] >= 'a' && codePoint_string[i] <='f'){
            codePoint = codePoint_string[i] - 'a' + 10;
            char bits[5] = "";
            hexToBin(bits, codePoint);
            //cout<< bits << endl;
            strcat(codePoint_binary, bits);
        }
        
        if (codePoint_string[i] >= 'A' && codePoint_string[i] <='F'){
            codePoint = codePoint_string[i] - 'A' + 10;
            char bits[5] = "";
            hexToBin(bits, codePoint);
            //cout<< bits << endl;
            strcat(codePoint_binary, bits);
        }
        
    
    }
    
    codePoint = binaryStringToInt(codePoint_binary);
    
    
    if (codePoint <= 0x007F){
        
        char encoded_binaryString[9] = "";

        int codePoint_position = strlen(codePoint_binary) - 1;
        
        encoded_binaryString[0] = '0';
        
        for( int index = 7; index >= 1 ; index--){
            encoded_binaryString[index] = codePoint_binary[codePoint_position];
            codePoint_position--;
        }
        
        cout << setfill('0') << setw(2) <<  hex << binaryStringToInt(encoded_binaryString) << endl;
        
    }
    else if (codePoint >= 0x0080 && codePoint <= 0x07FF){
        
        char encoded_binaryString[17] = "";
        int codePoint_position = strlen(codePoint_binary) - 1;
        
        encoded_binaryString[0] = encoded_binaryString[1] = encoded_binaryString[8] = '1';
        encoded_binaryString[2] = encoded_binaryString[9] = '0';
        
        //cout << strlen(codePoint_binary) << endl;
        
        for( int index = 15; index >= 3; index--){
            
            if(index == 9){
                index = index - 2;
            }
            
            encoded_binaryString[index] = codePoint_binary[codePoint_position];
            codePoint_position--;
            
            
        }
        
        cout << setfill('0') << setw(4) <<  hex << binaryStringToInt(encoded_binaryString) << endl;    
        
    }
    else if (codePoint >= 0x0800 && codePoint <= 0xFFFF){
        char encoded_binaryString[25] = "";
        int codePoint_position = strlen(codePoint_binary) - 1;
        
        encoded_binaryString[0] = encoded_binaryString[1] = encoded_binaryString[2]= encoded_binaryString[8] = encoded_binaryString[16] = '1';
        encoded_binaryString[3] = encoded_binaryString[9] = encoded_binaryString[17] =  '0';
        
        //cout << strlen(codePoint_binary) << endl;
        
        for( int index = 23; index >= 4; index--){
            
            if(index == 17 || index == 9){
                index = index - 2;
            }
            
            encoded_binaryString[index] = codePoint_binary[codePoint_position];
            codePoint_position--;
        }

        cout << setfill('0') << setw(6) <<  hex << binaryStringToInt(encoded_binaryString) << endl;    
        
        
    }
    else if (codePoint >= 0x10000 && codePoint <= 0x10FFFF){
        
        char encoded_binaryString[33] = "";
        int codePoint_position = strlen(codePoint_binary) - 1;
        
        encoded_binaryString[0] = encoded_binaryString[1] = encoded_binaryString[2]= encoded_binaryString[8] = encoded_binaryString[16] = encoded_binaryString[24] = '1';
        encoded_binaryString[3]= '1';
        encoded_binaryString[4] = encoded_binaryString[9] = encoded_binaryString[17] = encoded_binaryString[25] = '0';
        
        //cout << strlen(codePoint_binary) << endl;
        
        for( int index = 31; index >= 5; index--){
            
            if(index == 25 || index == 17 || index == 9){
                index = index - 2;
            }
            
            encoded_binaryString[index] = codePoint_binary[codePoint_position];
            codePoint_position--;
        }
        cout << "ebs : " << encoded_binaryString << endl;
        cout << "strlen = " << strlen(codePoint_binary) << endl;
        
        cout << "val: " << binaryStringToInt(encoded_binaryString) << endl;
        
        cout << setfill('0') << setw(8) <<  hex << binaryStringToInt(encoded_binaryString) << endl;   
    }
    

    /// ################  Decoder  ################
    
    
    string encoded_codePoint_string;
    unsigned long encoded_codePoint;
    char encoded_codePoint_binary[33] = "";
    
    cout << "Enter number for decoding : ";//FARA SPATIU
    getline(cin, encoded_codePoint_string, '\n');
    
    for (long i=0; i < encoded_codePoint_string.size(); i++){
        
        if (encoded_codePoint_string[i] >= '0' && encoded_codePoint_string[i] <='9'){
            encoded_codePoint = encoded_codePoint_string[i] - '0';
            char bits[5] = "";
            hexToBin(bits, encoded_codePoint);
            //cout<< bits << endl;
            strcat(encoded_codePoint_binary, bits);
        }
        
        if (encoded_codePoint_string[i] >= 'a' && encoded_codePoint_string[i] <='f'){
            encoded_codePoint = encoded_codePoint_string[i] - 'a' + 10;
            char bits[5] = "";
            hexToBin(bits, encoded_codePoint);
            //cout<< bits << endl;
            strcat(encoded_codePoint_binary, bits);
        }
        
        if (encoded_codePoint_string[i] >= 'A' && encoded_codePoint_string[i] <='F'){
            encoded_codePoint = encoded_codePoint_string[i] - 'A' + 10;
            char bits[5] = "";
            hexToBin(bits, encoded_codePoint);
            //cout<< bits << endl;
            strcat(encoded_codePoint_binary, bits);
        }
    }
    
    encoded_codePoint = binaryStringToInt(encoded_codePoint_binary);
    
    cout << encoded_codePoint_binary << endl;
    
    for(int i = 0; i <= 32; i++){
        cout << encoded_codePoint_binary[i];
    }
    cout << endl;
    
    if(encoded_codePoint_binary[0] == '1' && encoded_codePoint_binary[1] == '1' && encoded_codePoint_binary[2] == '1' && encoded_codePoint_binary[3] == '1'){
        
        if(encoded_codePoint_binary[4] == '1' || encoded_codePoint_binary[8] == '0' || encoded_codePoint_binary[9] == '1'
                || encoded_codePoint_binary[16] == '0' || encoded_codePoint_binary[17] == '1' || encoded_codePoint_binary[24] == '0'
                ||encoded_codePoint_binary[25] == '1'){
            cout << "invalid input! 1";
        }else{
            
            char decoded[22] = "";
            
            int position_encoded = strlen(encoded_codePoint_binary) - 1;
            for( int index = 20; index >= 0; index--){
                
                if(position_encoded == 25 || position_encoded == 17 || position_encoded == 9){
                    position_encoded -= 2;
                }
                decoded[index] = encoded_codePoint_binary[position_encoded];
                position_encoded--;
            }
            
            cout << setfill('0') << setw(8) <<  hex << binaryStringToInt(decoded) << endl;
        }
        //exit(1);
        return 0;
    }//end of case1
    
    if( encoded_codePoint_binary[0] == '1' && encoded_codePoint_binary[1] == '1' && encoded_codePoint_binary[2] == '1' ){
        
        if(encoded_codePoint_binary[3] == '1' || encoded_codePoint_binary[8] == '0' || encoded_codePoint_binary[9] == '1'
                || encoded_codePoint_binary[16]=='0' || encoded_codePoint_binary[17] == '1'){
            cout << "invalid ! 2";
        }else{

            char decoded[17] = "";

            int position_encoded = strlen(encoded_codePoint_binary) - 1;
            for( int index = 15; index >= 0; index--){

                if(position_encoded == 17 || position_encoded == 9){
                    position_encoded -= 2;
                }
                decoded[index] = encoded_codePoint_binary[position_encoded];
                position_encoded--;
            }

            cout << setfill('0') << setw(6) <<  hex << binaryStringToInt(decoded) << endl;
        }
        //exit(1);
        return 0;
        
    }//end of case 2
    
    if( encoded_codePoint_binary[0] == '1' && encoded_codePoint_binary[1] == '1' ){
        
        if(encoded_codePoint_binary[2] == '1' || encoded_codePoint_binary[8] == '0' || encoded_codePoint_binary[9] == '1'){
            cout << "invalid ! 3";
        }else{
            char decoded[12] = "";

            int position_encoded = strlen(encoded_codePoint_binary) - 1;
            for( int index = 10; index >= 0; index--){

                if(position_encoded == 9){
                    position_encoded -= 2;
                }
                decoded[index] = encoded_codePoint_binary[position_encoded];
                position_encoded--;
            }

            cout << setfill('0') << setw(4) <<  hex << binaryStringToInt(decoded) << endl;
        }
        //exit(1);
        return 0;
    }//end of case3
    
    if( encoded_codePoint_binary[0] == '1' ){
            cout << "invalid !4 ";
    }else{
            
        char decoded[8] = "";
        int position_encoded = strlen(encoded_codePoint_binary) - 1;

        for( int index = 6; index >= 0; index--){

            decoded[index] = encoded_codePoint_binary[position_encoded];
            position_encoded--;
        }

        cout << setfill('0') << setw(2) <<  hex << binaryStringToInt(decoded) << endl;
    }
    
    return 0;
}

