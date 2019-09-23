/*
  
   Project name : Engine control unit
   Company name : Skillfinity Technologies
   Author names : Ullas, Prashanth, Megha, Shivu

*/

//***********************************************************************************************************************************************************************************************************

// Engine control unit main program

 #include<stdio.h>
 #include<string.h>
 #include<stdlib.h> 
 #include<unistd.h>

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Main program code

int main()
{

// Initializtion of variables needed

     int Speed, Rpm, Brakes, Key;
     int MaxSpeed, MinSpeed, RpmMaxSpeed, RpmMinSpeed, Req, Time;   
     int GeneratedSpeed, GeneratedRpm;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
// Terminal Based Menu && Monitor REQ status
begin:
     printf("Enter the REQ status 0 : 1\n");
     scanf("%d",&Req);
     printf("\n");
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
// If REQ = 1 the continue the program

   if(Req == 1)
      {
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Take data from the user and StoreStringBuffer in variables        
  
          printf("Minimum Speed\n");                   // Maximum Speed 
          printf("Maximum Speed\n");                   // Minimum Speed
          scanf("%d %d",&MinSpeed, &MaxSpeed);
          printf("\n");

          printf("Minimum RPM\n");                      // Maximum RPM
          printf("Maximum RPM\n");                      // Minimum RPM
          scanf("%d %d",&RpmMinSpeed, &RpmMaxSpeed);
          printf("\n");
         
          printf("Time Duration\n");                    // Time intervals
          scanf("%d",&Time);
          printf("\n");

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Writing the data into SIMULATION_DATA file

   FILE *fptr = fopen("SimulationData","w");

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Generating values based on the user inputs

           for(GeneratedSpeed = MinSpeed, GeneratedRpm = RpmMinSpeed; GeneratedSpeed < MaxSpeed && GeneratedRpm < RpmMaxSpeed; GeneratedSpeed = GeneratedSpeed + Time, GeneratedRpm = GeneratedRpm + Time)
             {

                 printf("Enter the Vehicle Key status : ON : 1 ; OFF : 2 ; IGNITION : 3\n");
                 scanf("%d",&Key);
                 printf("\n");               
   
                 printf("Brake Status\n");
                 scanf("%d",&Brakes);
                 printf("\n");

                 fprintf(fptr,"<KEY:%d><BRAKES:%d><REQ:%d><SPEED:%d><RPM:%d>\n",Key,Brakes,Req,GeneratedSpeed,GeneratedRpm);

             }

       fclose(fptr);                            //Closing the opened SimulationData file

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Initializing the Char Buffers for storing the data that will be read from SimulationData file

     char StoreStringBuffer[100] = {0};
     char temp[100]={0};
     char m[100]={0};
     char SpeedBuffer[100]={0};
     char f[100]={0};
     char BrakeBuffer[10];
     char RpmBuffer[100]={0};

// Initializing the Char pointers to NULL
 
     char *p=NULL;
     char *s=NULL;
     char *o=NULL;
     char *ab=NULL;
     char *q=NULL;

// Initializing all the variables used to 0

     int a=0,b=0,k=0,c=0,l=0,v=0,t=0,DecodedSpeed=0,n=0,e=0,DecodedRpm=0,BrakeState=0;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Opening SimulationData file in read only mode

    fptr = fopen("SimulationData","r");

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Opening EcuData file for writing the data stored in SimulationData file

    FILE *fptr1 = fopen("EcuData","w");

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    if(fptr!=NULL)                       // Checking if File pointer is pointing to first char in SimulationData file
      {
        while(fgets(StoreStringBuffer,100,fptr))
         {
           s=strstr(StoreStringBuffer,"<KEY:");
           s += 5;                       // Incrementing the char pointer to point to KEY value
           char u[10];
           u[0]=*s;
           int KeyState=atoi(u);         // Converting KEY from ASCII value to Integer value

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

          s +=10;                        // Incrementing the char pointer to point to BRAKES value
          char DecodedRpm[10];
          DecodedRpm[0]=*s;
          int g=atoi(DecodedRpm);

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
         
           s +=16;                       // Incrementing the char pointer to point to SPEED value
           b=0;

             do
              {
                temp[b++]=*s;
                s++;
               }while(*s!='>');
           k=atoi(temp);
           memset(temp,0,100);

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        
          q=strstr(StoreStringBuffer,"<RPM:");       // Moving the char pointer to RPM location in given string

          if(q!=NULL)
           {
              q +=5;                     // Incrementing the pointer to RPM value
              c=0;

             do
               {
                 RpmBuffer[c++]=*q;      // Store the characters in char buffer
                 q++;
               }while(*q!='>');

                memset(StoreStringBuffer,0,100);     // Clearing the memory of StoreStringBuffer buffer
        
                l=atoi(RpmBuffer);
                memset(RpmBuffer,0,100);
           }

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 

// Printing the data onto the EcuData file

    if(KeyState==1)                      // Checking whether KEY status is ON  i.e 1
      {
          fprintf(fptr1,"<SPEED:%d><RPM:%d><BRAKES:%d>\n",k,l,g);
      }

    }                                    // Closing while loop 

        fclose(fptr1);

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
       
// Opening EcuData file in read mode
   
          fptr1 = fopen("EcuData","r");

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Opening EcuDataLog file in write mode

    FILE *fptr2 = fopen("EcuDataLog","w");

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Reading the data from EcuData file
 
      if(fptr1!=NULL)
       {
        while(fgets(m,100,fptr1))
         {
           p=strstr(m,"<SPEED:");                // Moving the char pointer until the <SPEED is encountered
             if(p!=NULL)
                {
                  p+=7;                          // Moving the char pointer until SPEED value
                  v=0;
                    do
                     {
                       SpeedBuffer[v++]=*p;      // Storing the SPEED value in the char buffer
                       p++;
                     }while(*p!='>');

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Fetching the RPM value from EcuData file

             p+=5;                               // Moving the char pointer to RPM value
             n=0;
             o=strstr(m,"<RPM:");
             if(o!= NULL)
             {
                 o+=5;
                 e=0;
                 do
                  {
                    f[n++]=*o;
                    o++;
                  }while(*o!='>');

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
// Fetching the BRAKES value from EcuData file
         
                 ab=strstr(m,"<BRAKES:");       // Moving the char pointer until <BRAKES: is encountered
                 if(ab!= NULL)
                 {
                   ab+=8;
                   BrakeBuffer[10];
                   BrakeBuffer[0]=*ab;
                  }
                 BrakeState=atoi(BrakeBuffer);

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Coverting both RPM and SPEED from ASCII values to integer values

                 DecodedRpm=atoi(f);      
                 DecodedSpeed=atoi(SpeedBuffer);

// Clearing the char buffers of EcuData string and Speed buffers

                 memset(m,0,100);    
                 memset(SpeedBuffer,0,100);
      }
  }

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

   int DecodedGear;                                // Variable to StoreStringBuffer the decoded DecodedGear value
   char *DecodedBrakeStatus=NULL;                  // Char pointer to StoreStringBuffer the BRAKE status
   static   int  Index=1;                          // variable to StoreStringBuffer the index value

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
// Decoding the Gear value based on the Speed value obtained

// Speed 0 - 10 --> Gear 1

          if(fptr2!=NULL)
            {
               switch(DecodedSpeed)
                 {
                    case 0 ... 10:
                     {
                         fprintf(fptr2,"<SPEED:%d><RPM:%d><GEAR:1><BRAKES:%d>\n",DecodedSpeed, DecodedRpm, BrakeState);
                         DecodedGear=1;

                             if(BrakeState==1)
                              {
                                  DecodedBrakeStatus = "APPLIED";
                              }
                            else
                              {
                                  DecodedBrakeStatus = "NOT APPLIED"; 
                              }
  
                            break; 
                     }

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Speed 11 - 25 --> Gear 2

                  case 11 ... 25:
                   {
                        fprintf(fptr2,"<SPEED:%d><RPM:%d><GEAR:2><BRAKES:%d>\n",DecodedSpeed, DecodedRpm, BrakeState);
                        DecodedGear=2;

                          if(BrakeState==1)
                           {
                               DecodedBrakeStatus = "APPLIED";
                           }
                          else
                           {
                               DecodedBrakeStatus = "NOT APPLIED"; 
                           }

                         break;
                  }

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Speed 26 - 40 --> Gear 3

                case 26 ... 40:
                 {
                      fprintf(fptr2,"<SPEED:%d><RPM:%d><GEAR:3><BRAKES:%d>\n",DecodedSpeed,DecodedRpm,BrakeState);
                      DecodedGear=3;

                       if(BrakeState==1)
                        {
                             DecodedBrakeStatus = "APPLIED";
                        }
                       else
                        {
                             DecodedBrakeStatus = "NOT APPLIED";
                        }
 
                        break;
                 }

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Speed 41 - 60 --> Gear 4

              case 41 ... 60:
                {
                       fprintf(fptr2,"<SPEED:%d><RPM:%d><GEAR:4><BRAKES:%d>\n",DecodedSpeed,DecodedRpm,BrakeState);
                       DecodedGear=4;
  
                       if(BrakeState==1)
                        {
                             DecodedBrakeStatus = "APPLIED";
                        }
                       else
                        {
                             DecodedBrakeStatus = "NOT APPLIED";
                        }
 
                        break;
               }

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        
// Speed 61 - above --> Gear 5

             default:
              {
                      fprintf(fptr2,"<SPEED:%d><RPM:%d><GEAR:5><BRAKES:%d>\n",DecodedSpeed, DecodedRpm, BrakeState);
                      DecodedGear=5;
  
                      if(BrakeState==1)
                       {
                             DecodedBrakeStatus = "APPLIED";
                       }
                      else
                       {
                             DecodedBrakeStatus = "NOT APPLIED";
                       }
            
                       break;
             }
       }

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        
// Printing the values on terminal

            sleep(3);
            system("clear");

            printf("<SPEED:%d> <RPM:%d> <GEAR:%d>\n",DecodedSpeed, DecodedRpm, DecodedGear);

            printf("\n");
            
            printf("INDEX \t SPEED \t RPM \t GEAR \t BRAKE STATUS\n");
            printf("----- \t ----- \t --- \t ---- \t ------------\n"); 
            printf("  %d       %d     %d      %d       %s  \n", Index++, DecodedSpeed, DecodedRpm, DecodedGear, DecodedBrakeStatus);
            
      }
}
       
        fclose(fptr2);                       // Closing the EcuDataLog file
      return 0; 
            
         }

        
     }


}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Incase Req is '0' goto Req request from user and ask for input

       else
        {
           goto begin;
           return 0;
         }
}    

//***************************************************************End of the Code***************************************************************************************************************************  
