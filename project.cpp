/****************************************************************************
*HOW TO USE:
*
*1)You choose the address of the source(sender)
*
*2)You choose the adress of the destination(receiver)
*
*3)You enter the data (with range from 1-1000)
*
*4)It prints the data with errors on the screen
*
******************************************************************************/

#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>




int binaryadd(int x)//Adding (changing) binary data for error
{
if(x==1)
return 0;
return 1;
}

/*****************************************************************/

int findsize(int mine)//To Find the size of the data to be put in the array
{
	int m=0;
	while(mine){
	mine=mine/10;
	m++;}
return m;	
}

/*****************************************************************/

void toarray(int mine,int *data)//Changes from int to array of int where each a[i] has one element
{
int size;
		size=findsize(mine);
		
		
	for(int i=0;i<size;i++){
			if(mine>=10)
			{data[size-i-1]=mine%10;
			mine/=10;}
			data[0]=mine;}
}
/*****************************************************************/

int fromarray(int *data,int size)//Opposite of toarray (from an array to a single int)
{
	int mine=0;

	for(int i=0;i<size;i++)	
	{
	mine+=data[i]*(int)pow(10,size-i-1);}

return mine;
} 	

/*****************************************************************/

int bin_to_dec(int m)//Changes from binary to decimal
{
	int n[10],size,sum=0;
	toarray(m,n);
	size=findsize(m);

for(int i=0;i<size;i++)
if(n[i]==1)
sum+=(int)pow(2,size-i-1);

return sum;}

/*****************************************************************/

int dec_to_bin (int n)//Changes from decimal to binary
{
	int sum=0,i=0;
	while(n)
	{sum+=((n%2)*(int)pow(10,i));
         n/=2;
		 i++;
	}
return sum;};


/*****************************************************************/

class frame
{

public:
	int dest[4],source[4],data[10],crc[3],sizeofdata[1],sizeofcrc[1];

};

/*****************************************************************/

class receiver{

public:

receiver(int add):rec_addr(add),commonG(1010){};//Receiver Constructor

void check_data(frame F)//Check if there is error
{		
	if(fromarray(F.dest,4)!=rec_addr)
		cout<<"\n\nMY address is:"<<rec_addr<<"\nDATA IS NOT MINE"<<endl;
	else 
		{int M,N,O,Sum,result;
		
		M=bin_to_dec(fromarray(F.data,F.sizeofdata[0]));
		O=bin_to_dec(fromarray(F.crc,F.sizeofcrc[0]));
		N=bin_to_dec(commonG);
	
	
	

		cout<<"\n\nSource of data is :"<<fromarray(F.source,4)<<endl;
		cout<<"Destination for data:"<<fromarray(F.dest,4)<<endl;
		cout<<"Data with errors now in receiver:"<<M<<endl;
		cout<<"with crc is:"<<O<<endl;

	Sum=M-O;
	result=Sum%N;
	if(result==0)
	{cout<<"Data is transmitted successfully"<<endl;
	cout<<"Even if there is error";}
	else 
		cout<<"Data is NOT transmitted successfully"<<endl;

	 }
 }

/***************/

void receive_data(frame F)//Receives the frame from the channel
{
	check_data(F);}

private:
	int rec_addr,commonG;

};

/*****************************************************************/

class channel{

public:
		
	void Add_error(frame &F)//Add error to the data and the crc 
							//Then prints on the screen number and position of errors	
	{int num_err,pos_err,random_integer;
	srand((unsigned)time(0));    
	 random_integer = rand();

		num_err=random_integer%(F.sizeofdata[0]+F.sizeofcrc[0]);
		cout<<"\n\nNumber of errors is: "<<num_err<<endl;
		for(int k=0;k<num_err;k++){
			pos_err=rand()%(F.sizeofdata[0]+F.sizeofcrc[0]);
			cout<<"Position of errors is: "<<pos_err<<endl;
			
				if(pos_err<F.sizeofdata[0])
					F.data[pos_err]=binaryadd(F.data[pos_err]);
				else
					F.crc[pos_err-F.sizeofdata[0]]=binaryadd(F.crc[pos_err-F.sizeofdata[0]]);}
									
	
		
	}
/***********/

	void To_receiver(frame F,receiver R){//Gives the frame to the receiver
		
		R.receive_data(F);
	}

/***********/

	void channel_source(frame &F){//Takes the frame from the sender
		cout<<"\nSender of address :"<<fromarray(F.source,4)<<endl;
		cout<<"Receiver of address :"<<fromarray(F.dest,4)<<endl;
		cout<<"Data is :"<<bin_to_dec(fromarray(F.data,F.sizeofdata[0]))<<endl;
		cout<<"with crc is:"<<bin_to_dec(fromarray(F.crc,F.sizeofcrc[0]))<<endl;
	Add_error(F);
	}
	
};



/*****************************************************************/
class sender{

public:
	sender(int add):send_add(add),commonG(1010){};//Sender Constructor


int createCRC(frame F,int size)//create CRC 
	{int M,N,CRC;
	
	
	M=fromarray(F.data,size);
	
	M=M/(int)pow(10,10-F.sizeofdata[0]);
	M=bin_to_dec(M);
	
	N=bin_to_dec(commonG);
	CRC=M%N;
			return CRC;}

/***********/

frame Add_data()//Creates the frame
	{frame F;
				
	int r_add,s_add,temp;
	cout<<"Enter the address of the sender"<<endl;
	cout<<"Possible adresses are:1010-1100"<<endl;
		cin>>s_add;
		
		while((s_add!=1010)&&(s_add!=1100))
		{cout<<"Possible adresses are:1010-1100"<<endl;
		cin>>s_add;}
		
		toarray(s_add,F.source);
		
		cout<<"Enter the address of the destination"<<endl;
		cout<<"Possible adresses are:1111-1000"<<endl;
		cin>>r_add;
		while((r_add!=1111)&&(r_add!=1000))
		{cout<<"Possible adresses are:1111-1000"<<endl;
		cin>>r_add;}
		
		toarray(r_add,F.dest);
	

		cout<<"Enter the data to be transmitted"<<endl;
		cout<<"Possible range (1-1000)"<<endl;
		cin>>temp;
	temp=dec_to_bin(temp);
	F.sizeofdata[0]=findsize(temp);
	cout<<"\n\nSize of data is "<<F.sizeofdata[0]<<endl;
	temp*=(int)pow(10,10-F.sizeofdata[0]);
	cout<<"Data in binary will be  "<<temp<<" with "<<10-F.sizeofdata[0]<<" zeros added to the left" ;
	toarray(temp,F.data);
	
	
	temp=createCRC(F,10);

	temp=dec_to_bin(temp);
	F.sizeofcrc[0]=findsize(temp);
	
	toarray(temp,F.crc);
		
	return F;
		
		
	}
/***********/

void Send_data(frame &F,channel C)//Gives the frame to the channel
{C.channel_source(F);
}

private:
	int send_add,commonG;
	
}; 


/************************************************************************/

int main(){

	
sender s(1010),n(1100),s_dummy(0000);
receiver r(1111),m(1000);
channel c;
frame f;

	
f=s_dummy.Add_data();
s_dummy.Send_data(f,c);

c.To_receiver(f,r);
c.To_receiver(f,m);

getch();	
	return 0;
}
