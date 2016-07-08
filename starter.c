# include <stdio.h>
# include <stdlib.h>

int main(int argc, char* argv[])
{
	int i,j,k;
	FILE* in,*fp,*out;
	char* bobo= malloc(sizeof(char)*300024);

	int board[9][9];
	int grid_no[9][9];
	int g=0,v;
	int count=0;
	int gridding=1;
	int flag=0;
	in = fopen(argv[1],"r+");
	fp = fopen("initial_part.txt","r");
	out = fopen("initialize-Sudoku.soar","w+");
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			grid_no[i][j]= gridding;
			count++;
			if(count==3) {
				gridding++;
				count=0;
			}
			fscanf(in, "%s ",bobo);
			if(!strcmp(bobo,".")){
				board[i][j]=0;
			}else{
				board[i][j]= atoi(bobo);
			}
		}
		flag++;
		if(flag==3){
			flag=0;
		}else{
			gridding-=3;
		}
	}
	
	fclose(in);
	fseek(fp,0,SEEK_END);
	j=ftell(fp);
	rewind(fp);
	fread(bobo,j,1,fp);
	fclose(fp);
	fwrite(bobo,j,1,out);
	fprintf(out, "\n");
	fprintf(out, "\n");
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(board[i][j]!=0){
				fprintf(out, "(<cell-%d%d> ^row %d ^col %d ^grid %d ^value %d ^count %d)\n",i+1,j+1,i+1,j+1,grid_no[i][j],board[i][j],0 );
			}else{
			fprintf(out, "(<cell-%d%d> ^row %d ^col %d ^grid %d ^value %d ^count %d ^case 1 ^case 2 ^case 3 ^case 4 ^case 5 ^case 6 ^case 7 ^case 8 ^case 9)\n",i+1,j+1,i+1,j+1,grid_no[i][j],board[i][j],9 );
			}
		}fprintf(out, "\n");
	}
	for(i=0;i<9;i++){
		k=0;
		for(j=0;j<9;j++){
			if(board[i][j]==0) k++;
		}
		for(j=0;j<9;j++){
			fprintf(out, "(<row%dcase%d> ^row %d ^case %d ^count %d )\n",i+1,j+1,i+1,j+1, k );
		}fprintf(out, "\n");
	}

	for(i=0;i<9;i++){
		k=0;
		for(j=0;j<9;j++){
			if(board[j][i]==0) k++;
		}
		for(j=0;j<9;j++){
			fprintf(out, "(<col%dcase%d> ^col %d ^case %d ^count %d )\n",i+1,j+1,i+1,j+1, k );
		}fprintf(out, "\n");
	}

	for(i=0;i<9;i++){
		k=0;
		g++;
		if(g%3==1) j=0;
		if(g%3==2) j=3;
		if(g%3==0) j=6;
		for(v=0;v<3;v++){
			if(board[i][j]==0) k++;
			if(board[i+1][j]==0)k++;
			if(board[i+2][j]==0)k++;
			j++;
		}
		for(j=0;j<9;j++){
			fprintf(out, "(<grid%dcase%d> ^grid %d ^case %d ^count %d )\n",g,j+1,g,j+1, k );
		}fprintf(out, "\n");
		i--;
		if(g%3==0) i=i+3;
	}


	fprintf(out, "}");

	return 0;
}