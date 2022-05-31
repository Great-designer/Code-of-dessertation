#include<stdio.h>
#include<string.h>
#include<ctype.h>

FILE *in;//输入
FILE *out;//输出
char buf[20010];//输入输出
int buftop;

void checkbegin()//执行结束后，这行应该拥有“1 绪论”
{
	fgets(buf,15010,in);//含空白符
	char *a=strstr(buf,"1");
	char *b=strstr(buf,"·");
	while(1)
	{
		int flag=1;
		if(a!=NULL&&b==NULL)
		{
			if(a!=buf)
			{
				char *i;
				for(i=a-1; i>=buf; i--)
				{
					if(isspace(*i)==0)//不是空白符
					{
						flag=0;
					}
				}
			}
			if(flag==1)
			{
				break;
			}
		}
		fgets(buf,15010,in);
		a=strstr(buf,"1");
		b=strstr(buf,"···");
	}
}

void process_escape()//处理转义字符，% $ & { } # _ ^ \替换为\% \$ \& \{ \} \# \_{} \^{} \backslash
{
	int len=strlen(buf);
	int i;
	for(i=0; i<len; i++) //维护i和buf
	{
		if(buf[i]=='%')
		{
			int j;
			for(j=len+1; j>i; j--) //后移一位。原本len的位置是\0
			{
				buf[j]=buf[j-1];
			}
			buf[i]='\\';
			i++;
			len++;
		}
		else if(buf[i]=='$')
		{
			int j;
			for(j=len+1; j>i; j--) //后移一位。原本len的位置是\0
			{
				buf[j]=buf[j-1];
			}
			buf[i]='\\';
			i++;
			len++;
		}
		else if(buf[i]=='&')
		{
			int j;
			for(j=len+1; j>i; j--) //后移一位。原本len的位置是\0
			{
				buf[j]=buf[j-1];
			}
			buf[i]='\\';
			i++;
			len++;
		}
		else if(buf[i]=='{')
		{
			int j;
			for(j=len+1; j>i; j--) //后移一位。原本len的位置是\0
			{
				buf[j]=buf[j-1];
			}
			buf[i]='\\';
			i++;
			len++;
		}
		else if(buf[i]=='}')
		{
			int j;
			for(j=len+1; j>i; j--) //后移一位。原本len的位置是\0
			{
				buf[j]=buf[j-1];
			}
			buf[i]='\\';
			i++;
			len++;
		}
		else if(buf[i]=='#')
		{
			int j;
			for(j=len+1; j>i; j--) //后移一位。原本len的位置是\0
			{
				buf[j]=buf[j-1];
			}
			buf[i]='\\';
			i++;
			len++;
		}
		else if(buf[i]=='_')
		{
			int j;
			for(j=len+3; j>i; j--) //后移三位。原本len的位置是\0
			{
				buf[j]=buf[j-3];
			}
			buf[i]='\\';
			buf[i+1]='_';
			buf[i+2]='{';
			buf[i+3]='}';
			i+=3;
			len+=3;
		}
		else if(buf[i]=='^')
		{
			int j;
			for(j=len+3; j>i; j--) //后移三位。原本len的位置是\0
			{
				buf[j]=buf[j-3];
			}
			buf[i]='\\';
			buf[i+1]='^';
			buf[i+2]='{';
			buf[i+3]='}';
			i+=3;
			len+=3;
		}
		else if(buf[i]=='\\')
		{
			int j;
			for(j=len+10; j>i; j--) //后移10位。原本len的位置是\0
			{
				buf[j]=buf[j-10];
			}
			buf[i+1]='b';
			buf[i+2]='a';
			buf[i+3]='c';
			buf[i+4]='k';
			buf[i+5]='s';
			buf[i+6]='l';
			buf[i+7]='a';
			buf[i+8]='s';
			buf[i+9]='h';
			buf[i+10]=' ';
			i+=10;
			len+=10;
		}
	}
}

int NUMBER_chapter;//当前章序号
int NUMBER_picture;//当前图序号
int NUMBER_code;//当前代码序号
char temptitle[20010];//处理标题

int process_title()//处理标题。对于款项不做处理
{
	int i=0;
	while(isdigit(buf[i]))//只要当前位仍然是数字
	{
		i++;
	}
	if(i!=0)//第一轮数字判定完毕，可能为章节条
	{
		if(buf[i]=='\0')//标题不能无内容
		{
			return 0;
		}
		if(buf[i]=='='||buf[i]=='-'||buf[i]=='+')//标题不能是公式
		{
			return 0;
		}
		char *a=strstr(buf,"、");
		if(a==&buf[i])//顿号是下一级，不是章标题
		{
			return 0;
		}
		if(buf[i]=='.')//可能为节条
		{
			i++;
			if(isdigit(buf[i]))//为节条
			{
				while(isdigit(buf[i]))//只要当前位仍然是数字
				{
					i++;
				}
				if(buf[i]=='.')//可能为条
				{
					i++;
					if(isdigit(buf[i]))//为条
					{
						while(isdigit(buf[i]))//只要当前位仍然是数字
						{
							i++;
						}
						if(buf[i]=='.')//可能为款项
						{
							return 0;//不做处理
						}
						while(isspace(buf[i]))//为节，去掉空白符
						{
							i++;
						}
						strcpy(temptitle,&buf[i]);//buf[i]指向第一个章标题处
						buf[0]='\\';
						buf[1]='s';
						buf[2]='u';
						buf[3]='b';
						buf[4]='s';
						buf[5]='e';
						buf[6]='c';
						buf[7]='t';
						buf[8]='i';
						buf[9]='o';
						buf[10]='n';
						buf[11]='{';
						buf[12]='\0';
						strcat(buf,temptitle);
						int len=strlen(buf);
						len--;
						while(isspace(buf[len]))//去掉末尾空白
						{
							len--;
						}
						len++;
						buf[len]='}';
						buf[len+1]='\0';
						return 1;//为条时处理完毕
					}
					i--;//为节，只是格式不规范
				}
				while(isspace(buf[i]))//为节，去掉空白符
				{
					i++;
				}
				strcpy(temptitle,&buf[i]);//buf[i]指向第一个章标题处
				buf[0]='\\';
				buf[1]='s';
				buf[2]='e';
				buf[3]='c';
				buf[4]='t';
				buf[5]='i';
				buf[6]='o';
				buf[7]='n';
				buf[8]='{';
				buf[9]='\0';
				strcat(buf,temptitle);
				int len=strlen(buf);
				len--;
				while(isspace(buf[len]))//去掉末尾空白
				{
					len--;
				}
				len++;
				buf[len]='}';
				buf[len+1]='\0';
				return 1;//为节时处理完毕
			}
			i--;//为章，只是格式不规范
		}
		while(isspace(buf[i]))//为章，去掉空白符
		{
			i++;
		}
		strcpy(temptitle,&buf[i]);//buf[i]指向第一个章标题处
		buf[0]='\\';
		buf[1]='c';
		buf[2]='h';
		buf[3]='a';
		buf[4]='p';
		buf[5]='t';
		buf[6]='e';
		buf[7]='r';
		buf[8]='{';
		buf[9]='\0';
		strcat(buf,temptitle);
		int len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='}';
		buf[len+1]='\0';
		NUMBER_chapter++;//更新章序号
		NUMBER_picture=1;//更新图序号
		NUMBER_code=1;//更新代码序号
		return 1;//含章
	}
	return 0;//不含章节条
}

int NUMBER_ref;//参考文献序号
char tempref[20010];//处理参考文献
char temprefnum[110];//序号

void process_ref()//处理文章中的参考文献。一行里面可能有多个参考文献，都要处理。
{
	int len=strlen(buf);
	int i;
	for(i=0; i<len; i++)
	{
		if(buf[i]=='[')//开始
		{
			int j=i;
			j++;
			while(isdigit(buf[j]))
			{
				j++;
			}
			if(buf[j]==']')//找到了
			{
				j++;
				strcpy(tempref,&buf[j]);//后半段存入
				sprintf(temprefnum,"%d",NUMBER_ref);//数字存入
				buf[i]='\0';
				strcat(buf,"\\upcite{");
				strcat(buf,temprefnum);//接上数字
				strcat(buf,"}");
				strcat(buf,tempref);//接上后半段
				NUMBER_ref++;
				len=strlen(buf);
				i+=strlen(temprefnum);
			}
		}
	}
	char *a=strstr(buf,"[");
	if(a==NULL)//找不到
	{
		return;
	}
	char *b=a;
	b++;
	while(isdigit(*b))
	{
		b++;
	}

	if(*b==']')//找到了
	{
		b++;
		strcpy(tempref,b);//后半段存入
		sprintf(temprefnum,"%d",NUMBER_ref);//数字存入
		*a='\0';
		strcat(buf,"\\upcite{");
		strcat(buf,temprefnum);//接上数字
		strcat(buf,"}");
		strcat(buf,tempref);//接上后半段
		NUMBER_ref++;
	}
}

char temppic[20010];//处理图片
char temppicnum[110];//序号

void process_figure()//处理图
{
	char *a=strstr(buf,"图");
	if(a!=buf)
	{
		return;
	}
	a+=strlen("图");
	if(!isspace(*a))//不是图注
	{
		return;
	}
	while(isspace(*a))//图注这里有空格
	{
		a++;
	}
	if(!isdigit(*a))//不是图注
	{
		return;
	}
	while(isdigit(*a))
	{
		a++;
	}
	if(*a!='.')//不是图注
	{
		return;
	}
	a++;
	if(!isdigit(*a))//不是图注
	{
		return;
	}
	while(isdigit(*a))
	{
		a++;
	}
	if(!isspace(*a))//不是图注
	{
		return;
	}
	while(isspace(*a))//跳过空白。a指向图片标题
	{
		a++;
	}
	strcpy(temppic,"\\begin{figure}[h!]\\centering\\includegraphics[width=0.4\\textwidth]{figure/");//图片前缀
	sprintf(temppicnum,"%d",NUMBER_chapter);//章号
	strcat(temppic,temppicnum);
	strcat(temppic,".");
	sprintf(temppicnum,"%d",NUMBER_picture);//图号
	NUMBER_picture++;
	strcat(temppic,temppicnum);
	strcat(temppic,".pdf}\\caption{");
	strcat(temppic,a);
	strcat(temppic,"}\\label{fig-sample}\\end{figure}");//图片后缀
	strcpy(buf,temppic);//粘贴回buf
}

int initmode;//第一个1特判

int iscode()//是代码。
{
	if(initmode==1)
	{
		return 0;
	}
	else if(buf[0]=='1'&&isspace(buf[1]))//以1开头并且下一位是空格
	{
		return 1;
	}
	else//其他情形必须返回
	{
		return 0;
	}
}

void process_code()//listing环境输出代码。这时当前行是1开头
{
	fprintf(out,"\\begin{lstlisting}[language={C},caption={示例代码},label={%d.%d},]\n",NUMBER_chapter,NUMBER_code);//代码头。每行末尾有\n，含有章数，代码数
	while(isdigit(buf[0]))//只要下一行仍旧以数字开头就仍旧位于代码段中
	{
		int i=0;
		while(isdigit(buf[i]))//只要当前位仍然是数字，就直接吞掉。根据排版约定，不管是否正确
		{
			i++;
		}
		fprintf(out,"%s\n",&buf[i]);//输出。不增加新的一行
		fgets(buf,15010,in);//最后读入新的一行，检查是否应该终止
		char *a=strstr(buf,"北京航空航天大学毕业设计");
		if(a!=NULL)
		{
			fgets(buf,15010,in);//重新读入一遍
		}
		int len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
	}
	fprintf(out,"\\end{lstlisting}\n");
	NUMBER_code++;//更新代码序号
	char *a=strstr(buf,"代码");
	if(a==buf)//最后一行会是代码题注，也要直接吞掉
	{
		fgets(buf,15010,in);//读入新的一行
		int len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
	}
}

void process_text()//这一行里拥有绪论——未完成。执行结束后，这行应该拥有“结论”
{
	fprintf(out,"%% !Mode:: \"TeX:UTF-8\"\n");
	NUMBER_chapter=1;//当前章序号
	NUMBER_picture=1;//当前图序号
	NUMBER_ref=1;//参考文献序号
	NUMBER_code=1;//代码序号
	char *a=strstr(buf,"结论");
	initmode=1;//特判
	while(1)
	{
		if(iscode())//单独输出listing环境，不走buf
		{
			process_code();
		}
		else
		{
			process_escape();//处理转义字符
			int tit=process_title();//处理标题
			initmode=0;//处理过1，特判结束
			if(tit==0)//不含新的标题
			{
				process_ref();//处理文章中的参考文献
				process_figure();//处理图
			}
			fprintf(out,"%s\n\n",buf);//输出并增加新的一行
			fgets(buf,15010,in);//最后读入新的一行，检查是否应该终止
			char *a=strstr(buf,"北京航空航天大学毕业设计");
			if(a!=NULL)
			{
				fgets(buf,15010,in);//重新读入一遍
			}
			int len=strlen(buf);
			len--;
			while(isspace(buf[len]))//去掉末尾空白
			{
				len--;
			}
			len++;
			buf[len]='\0';
		}
		a=strstr(buf,"结论");
		int flag=1;//检查结论
		if(a!=NULL)
		{
			if(a!=buf)
			{
				char *i;
				for(i=a-1; i>=buf; i--)//这里炸了。不应该是a-1
				{
					if(isspace(*i)==0)//不是空白符
					{
						flag=0;
					}
				}
			}
			if(flag==1)//循环终止
			{
				break;
			}
		}
	}
}

void process_conclusion()//结论部分
{
	fprintf(out,"%% !Mode:: \"TeX:UTF-8\"\n");
	fprintf(out,"\\chapter*{结论\\markboth{结论}{}}\n");
	fprintf(out,"\\addcontentsline{toc}{chapter}{结论}\n");
	fgets(buf,15010,in);//最后读入新的一行，检查是否应该终止
	char *a=strstr(buf,"北京航空航天大学毕业设计");
	if(a!=NULL)
	{
		fgets(buf,15010,in);//重新读入一遍
	}
	int len=strlen(buf);
	len--;
	while(isspace(buf[len]))//去掉末尾空白
	{
		len--;
	}
	len++;
	buf[len]='\0';
	a=strstr(buf,"致谢");
	while(a==NULL)
	{
		process_escape();//处理转义字符
		fprintf(out,"%s\n\n",buf);//输出并增加新的一行
		fgets(buf,15010,in);//最后读入新的一行，检查是否应该终止
		char *a=strstr(buf,"北京航空航天大学毕业设计");
		if(a!=NULL)
		{
			fgets(buf,15010,in);//重新读入一遍
		}
		int len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
		a=strstr(buf,"致谢");
		int flag=1;//检查致谢
		if(a!=NULL)
		{
			if(a!=buf)
			{
				char *i;
				for(i=a-1; i>=buf; i--)//这里炸了。不应该是a-1
				{
					if(isspace(*i)==0)//不是空白符
					{
						flag=0;
					}
				}
			}
			if(flag==1)//循环终止
			{
				break;
			}
		}
	}
	fprintf(out,"\\chapter*{致谢}\n");
	fprintf(out,"\\addcontentsline{toc}{chapter}{致谢}\n");
	fgets(buf,15010,in);//最后读入新的一行，检查是否应该终止
	a=strstr(buf,"北京航空航天大学毕业设计");
	if(a!=NULL)
	{
		fgets(buf,15010,in);//重新读入一遍
	}
	len=strlen(buf);
	len--;
	while(isspace(buf[len]))//去掉末尾空白
	{
		len--;
	}
	len++;
	buf[len]='\0';
	a=strstr(buf,"参");
	char *b=strstr(buf,"考");
	char *c=strstr(buf,"文");
	char *d=strstr(buf,"献");
	while(!(a!=NULL&&b!=NULL&&c!=NULL&&d!=NULL))
	{
		process_escape();//处理转义字符
		fprintf(out,"%s\n\n",buf);//输出并增加新的一行
		fgets(buf,15010,in);//最后读入新的一行，检查是否应该终止
		char *a=strstr(buf,"北京航空航天大学毕业设计");
		if(a!=NULL)
		{
			fgets(buf,15010,in);//重新读入一遍
		}
		int len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
		a=strstr(buf,"参");
		b=strstr(buf,"考");
		c=strstr(buf,"文");
		d=strstr(buf,"献");
		int flag=1;//检查致谢
		if(a!=NULL&&b!=NULL&&c!=NULL&&d!=NULL)
		{
			if(a!=buf)
			{
				char *i;
				for(i=a-1; i>=buf; i--)//这里炸了。不应该是a-1
				{
					if(isspace(*i)==0)//不是空白符
					{
						flag=0;
					}
				}
			}
			if(flag==1)//循环终止
			{
				break;
			}
		}
	}
	fprintf(out,"\\cleardoublepage\n");
}

char NUMBER_appchapter;//当前章序号
char NUMBER_apppicture;//当前图序号
char NUMBER_appcode;//当前代码序号
char tempapptitle[20010];//暂存

int process_apptitle()//附录的标题
{
	char *a=strstr(buf,"附录");
	if(a==buf)//可能是附录标题
	{
		a+=strlen("附录");
		while(isspace(*a))
		{
			a++;
		}
		if(!isalpha(*a))//这位不是字母
		{
			return 0;//不含标题
		}
		while(isalpha(*a))
		{
			a++;
		}
		while(isspace(*a))//之后a指向标题文本
		{
			a++;
		}
		strcpy(tempapptitle,a);//a指向第一个章标题处
		buf[0]='\\';
		buf[1]='c';
		buf[2]='h';
		buf[3]='a';
		buf[4]='p';
		buf[5]='t';
		buf[6]='e';
		buf[7]='r';
		buf[8]='{';
		buf[9]='\0';
		strcat(buf,tempapptitle);
		int len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='}';
		buf[len+1]='\0';
		NUMBER_appchapter++;//更新章序号
		NUMBER_apppicture=1;//更新图序号
		NUMBER_appcode=1;//更新代码序号
		return 1;//含章
	}
	return 0;//不含标题
}

char tempapppic[20010];//处理图片
char tempapppicnum[110];//序号

void process_appfigure()//附录中的图
{
	char *a=strstr(buf,"图");
	if(a!=buf)
	{
		return;
	}
	a+=strlen("图");
	if(!isspace(*a))//不是图注
	{
		return;
	}
	while(isspace(*a))//图注这里有空格
	{
		a++;
	}
	if(!isalpha(*a))//不是图注
	{
		return;
	}
	while(isalpha(*a))
	{
		a++;
	}
	if(!isdigit(*a))//不是图注
	{
		return;
	}
	while(isdigit(*a))
	{
		a++;
	}
	if(!isspace(*a))//不是图注
	{
		return;
	}
	while(isspace(*a))//跳过空白。a指向图片标题
	{
		a++;
	}
	strcpy(tempapppic,"\\begin{figure}[h!]\\centering\\includegraphics[width=0.4\\textwidth]{figure/");//图片前缀
	sprintf(tempapppicnum,"%c",NUMBER_appchapter);//章号
	strcat(tempapppic,tempapppicnum);
	strcat(tempapppic,".");
	sprintf(tempapppicnum,"%d",NUMBER_apppicture);//图号
	NUMBER_apppicture++;
	strcat(tempapppic,tempapppicnum);
	strcat(tempapppic,".pdf}\\caption{");
	strcat(tempapppic,a);
	strcat(tempapppic,"}\\label{fig-sample}\\end{figure}");//图片后缀
	strcpy(buf,tempapppic);//粘贴回buf
}

void process_appcode()
{
	fprintf(out,"\\begin{lstlisting}[language={C},caption={示例代码},label={%c%d},]\n",NUMBER_appchapter,NUMBER_appcode);//代码头。每行末尾有\n，含有章数，代码数
	while(isdigit(buf[0]))//只要下一行仍旧以数字开头就仍旧位于代码段中
	{
		int i=0;
		while(isdigit(buf[i]))//只要当前位仍然是数字，就直接吞掉。根据排版约定，不管是否正确
		{
			i++;
		}
		fprintf(out,"%s\n",&buf[i]);//输出。不增加新的一行
		fgets(buf,15010,in);//最后读入新的一行，检查是否应该终止
		char *a=strstr(buf,"北京航空航天大学毕业设计");
		if(a!=NULL)
		{
			fgets(buf,15010,in);//重新读入一遍
		}
		int len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
	}
	fprintf(out,"\\end{lstlisting}\n");
	NUMBER_appcode++;//更新代码序号
	char *a=strstr(buf,"代码");
	if(a==buf)//最后一行会是代码题注，也要直接吞掉
	{
		fgets(buf,15010,in);//读入新的一行
		int len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
	}
}

void process_appendix()//附录部分——待完成——处理标题
{
	fprintf(out,"%% !Mode:: \"TeX:UTF-8\"\n");
	NUMBER_appchapter='A';//当前章序号
	NUMBER_apppicture=1;//当前图序号
	NUMBER_appcode=1;//当前代码序号
	while(1)
	{
		if(iscode())//单独输出listing环境，不走buf，可以复用
		{
			process_appcode();
		}
		else
		{
			process_escape();//处理转义字符
			int tit=process_apptitle();//处理标题
			if(tit==0)//不含新的标题
			{
				process_appfigure();//处理图
			}
			fprintf(out,"%s\n\n",buf);//输出并增加新的一行
			char *tt=fgets(buf,15010,in);//最后读入新的一行，检查是否应该终止
			if(tt==NULL)
			{
				break;
			}
			char *a=strstr(buf,"北京航空航天大学毕业设计");
			if(a!=NULL)
			{
				char *tt=fgets(buf,15010,in);//重新读入一遍
				if(tt==NULL)
				{
					break;
				}
			}
			int len=strlen(buf);
			len--;
			while(isspace(buf[len]))//去掉末尾空白
			{
				len--;
			}
			len++;
			buf[len]='\0';
		}
	}
}

void printbibs()
{
	
}

void checkappbegin()//附录A开头
{
	fgets(buf,15010,in);//含空白符
	char *a=strstr(buf,"附录");
	char *b=strstr(buf,"A");
	while(1)
	{
		int flag=1;
		if(a!=NULL&&b!=NULL)
		{
			if(a!=buf)
			{
				char *i;
				for(i=a-1; i>=buf; i--)
				{
					if(isspace(*i)==0)//不是空白符
					{
						flag=0;
					}
				}
			}
			if(flag==1)
			{
				break;
			}
		}
		fgets(buf,15010,in);
		a=strstr(buf,"附录");
		b=strstr(buf,"A");
	}
}

char studentID[70];//学号
int studentID_valid;//学号有效位
char category[70];//中图分类号
int category_valid;//中图分类号有效位
char title_ch[70];//中文标题
int title_ch_valid;//中文标题有效位
char subtitle_ch[70];//中文副标题
int subtitle_ch_valid;//中文副标题有效位
char title_en[70];//英文标题
int title_en_valid;//英文标题有效位
char subtitle_en[70];//英文副标题
int subtitle_en_valid;//英文副标题有效位
char school[70];//学院名
int school_valid;//学院名有效位
char major[70];//专业名
int major_valid;//专业名有效位
char author_ch[70];//作者名中文
int author_ch_valid;//作者名中文有效位
char author_en[70];//作者名英文
int author_en_valid;//作者名英文有效位
char teacher_ch[70];//导师名中文
int teacher_ch_valid;//导师名中文有效位
char teacher_en[70];//导师名英文
int teacher_en_valid;//导师名英文有效位
char thesisdate_year[70];//论文时间年
int thesisdate_year_valid;//论文时间年有效位
char thesisdate_month[70];//论文时间月
int thesisdate_month_valid;//论文时间月有效位

char assignReq1[60];//原始资料及设计1
int assignReq1_valid;
char assignReq2[60];//原始资料及设计2
int assignReq2_valid;
char assignReq3[60];//原始资料及设计3
int assignReq3_valid;
char assignReq4[60];//原始资料及设计4
int assignReq4_valid;
char assignReq5[60];//原始资料及设计5
int assignReq5_valid;
char assignWork1[60];//工作内容1
int assignWork1_valid;
char assignWork2[60];//工作内容2
int assignWork2_valid;
char assignWork3[60];//工作内容3
int assignWork3_valid;
char assignWork4[60];//工作内容4
int assignWork4_valid;
char assignWork5[60];//工作内容5
int assignWork5_valid;
char assignWork6[60];//工作内容6
int assignWork6_valid;
char assignRef1[60];//参考文献1
int assignRef1_valid;
char assignRef2[60];//参考文献2
int assignRef2_valid;
char assignRef3[60];//参考文献3
int assignRef3_valid;
char assignRef4[60];//参考文献4
int assignRef4_valid;
char assignRef5[60];//参考文献5
int assignRef5_valid;
char assignRef6[60];//参考文献6
int assignRef6_valid;
char assignRef7[60];//参考文献7
int assignRef7_valid;
char assignRef8[60];//参考文献8
int assignRef8_valid;

char class_num[70];//班级号
int class_num_valid;//班级号有效位
char thesisbegin_year[70];//毕设开始时间年
int thesisbegin_year_valid;
char thesisbegin_month[70];//毕设开始时间月
int thesisbegin_month_valid;
char thesisbegin_date[70];//毕设开始时间日
int thesisbegin_date_valid;
char thesisend_year[70];//毕设结束时间年
int thesisend_year_valid;
char thesisend_month[70];//毕设结束时间月
int thesisend_month_valid;
char thesisend_date[70];//毕设结束时间日
int thesisend_date_valid;
char defense_year[70];//毕设答辩时间年
int defense_year_valid;
char defense_month[70];//毕设答辩时间月
int defense_month_valid;
char defense_date[70];//毕设答辩时间日
int defense_date_valid;
char abstract_ch[2010];//中文摘要
int abstract_ch_valid;//中文摘要有效位
char keyword_ch[210];//中文关键词
int keyword_ch_valid;//中文关键词有效位
char abstract_en[2010];//英文摘要
int abstract_en_valid;//英文摘要有效位
char keyword_en[210];//英文关键词
int keyword_en_valid;//英文关键词有效位

int checkcover()//用于提取信息的checkcover——要时刻检查样例。一共要处理47个
{
	char *a=strstr(buf,"学");//定位学号
	char *b=strstr(buf,"号");
	printf("%s\n",buf);
	if(a!=NULL&&b!=NULL&&studentID_valid!=1)
	{
		printf("OK1\n");
		b+=strlen("号");
		while(isspace(*b))
		{
			b++;
		}
		printf("%s\n",b);
		strcpy(studentID,b);
		studentID_valid=1;
		return 1;
	}
	a=strstr(buf,"分");
	b=strstr(buf,"类");
	char *c=strstr(buf,"号");
	if(a!=NULL&&b!=NULL&&c!=NULL&&category_valid!=1)
	{
		c+=strlen("号");
		while(isspace(*c))
		{
			c++;
		}
		strcpy(category,c);
		category_valid=1;
		return 1;
	}
	a=strstr(buf,"学");
	b=strstr(buf,"院");
	c=strstr(buf,"名");
	char *d=strstr(buf,"称");
	if(a!=NULL&&b!=NULL&&c!=NULL&&d!=NULL&&school_valid!=1)
	{
		d+=strlen("称");
		while(isspace(*d))
		{
			d++;
		}
		strcpy(school,d);
		d=school;
		d+=strlen(school);
		d-=strlen("学院");
		d--;
		while(isspace(*d))
		{
			d--;
		}
		d++;
		*d='\0';
		school_valid=1;
		return 1;
	}
	a=strstr(buf,"专");
	b=strstr(buf,"业");
	c=strstr(buf,"名");
	d=strstr(buf,"称");
	if(a!=NULL&&b!=NULL&&c!=NULL&&d!=NULL&&major_valid!=1)
	{
		d+=strlen("称");
		while(isspace(*d))
		{
			d++;
		}
		strcpy(major,d);
		d=major;
		d+=strlen(major);
		d-=strlen("专业");
		d--;
		while(isspace(*d))
		{
			d--;
		}
		d++;
		*d='\0';
		major_valid=1;
		return 1;
	}
	a=strstr(buf,"学");
	b=strstr(buf,"生");
	c=strstr(buf,"姓");
	d=strstr(buf,"名");
	if(a!=NULL&&b!=NULL&&c!=NULL&&d!=NULL&&author_ch_valid!=1)
	{
		d+=strlen("名");
		while(isspace(*d))
		{
			d++;
		}
		strcpy(author_ch,d);
		author_ch_valid=1;
		return 1;
	}
	a=strstr(buf,"指");
	b=strstr(buf,"导");
	c=strstr(buf,"教");
	d=strstr(buf,"师");
	if(a!=NULL&&b!=NULL&&c!=NULL&&d!=NULL&&teacher_ch_valid!=1)
	{
		printf("%d\n",teacher_ch_valid);
		printf("here\n");
		d+=strlen("师");
		while(isspace(*d))
		{
			d++;
		}
		strcpy(teacher_ch,d);
		teacher_ch_valid=1;
		printf("%d\n",teacher_ch_valid);
		fgets(buf,15010,in);//读入一行
		int len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
		c=buf;
		while(isspace(*c))
		{
			c++;
		}
		strcpy(thesisdate_year,c);//从这起始
		a=strstr(thesisdate_year,"年");//定位
		a--;
		while(isspace(*a))//倒着剪裁空格
		{
			a--;
		}
		a++;
		*a='\0';//在这里截断
		a=strstr(buf,"年");//定位
		a+=strlen("年");//a指向后半部分
		while(isspace(*a))
		{
			a++;
		}
		strcpy(thesisdate_month,a);//从这起始
		b=strstr(thesisdate_month,"月");//定位
		b--;
		while(isspace(*b))//倒着剪裁空格
		{
			b--;
		}
		b++;
		*b='\0';//在这里截断
		thesisdate_year_valid=1;
		thesisdate_month_valid=1;
		return 1;
	}
	a=strstr(buf,"设计技术要求");
	if(a!=NULL&&assignReq1_valid!=1)
	{
		fgets(buf,15010,in);//读入新的
		int len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
		a=strstr(buf,"工作内容");
		if(a==NULL)
		{
			strcpy(assignReq1,buf);
			assignReq1_valid=1;
			fgets(buf,15010,in);//读入新的
			int len=strlen(buf);
			len--;
			while(isspace(buf[len]))//去掉末尾空白
			{
				len--;
			}
			len++;
			buf[len]='\0';
			a=strstr(buf,"工作内容");
			if(a==NULL)
			{
				strcpy(assignReq2,buf);
				assignReq2_valid=1;
				fgets(buf,15010,in);//读入新的
				int len=strlen(buf);
				len--;
				while(isspace(buf[len]))//去掉末尾空白
				{
					len--;
				}
				len++;
				buf[len]='\0';
				a=strstr(buf,"工作内容");
				if(a==NULL)
				{
					strcpy(assignReq3,buf);
					assignReq3_valid=1;
					fgets(buf,15010,in);//读入新的
					int len=strlen(buf);
					len--;
					while(isspace(buf[len]))//去掉末尾空白
					{
						len--;
					}
					len++;
					buf[len]='\0';
					a=strstr(buf,"工作内容");
					if(a==NULL)
					{
						strcpy(assignReq4,buf);
						assignReq4_valid=1;
						fgets(buf,15010,in);//读入新的
						int len=strlen(buf);
						len--;
						while(isspace(buf[len]))//去掉末尾空白
						{
							len--;
						}
						len++;
						buf[len]='\0';
						a=strstr(buf,"工作内容");
						if(a==NULL)
						{
							strcpy(assignReq5,buf);
							assignReq5_valid=1;
							fgets(buf,15010,in);//读入新的
							int len=strlen(buf);
							len--;
							while(isspace(buf[len]))//去掉末尾空白
							{
								len--;
							}
							len++;
							buf[len]='\0';
						}
					}
				}
			}
		}
		fgets(buf,15010,in);//读入新的
		len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
		a=strstr(buf,"参考资料");
		if(a==NULL)
		{
			strcpy(assignWork1,buf);
			assignWork1_valid=1;
			fgets(buf,15010,in);//读入新的
			int len=strlen(buf);
			len--;
			while(isspace(buf[len]))//去掉末尾空白
			{
				len--;
			}
			len++;
			buf[len]='\0';
			a=strstr(buf,"参考资料");
			if(a==NULL)
			{
				strcpy(assignWork2,buf);
				assignWork2_valid=1;
				fgets(buf,15010,in);//读入新的
				int len=strlen(buf);
				len--;
				while(isspace(buf[len]))//去掉末尾空白
				{
					len--;
				}
				len++;
				buf[len]='\0';
				a=strstr(buf,"参考资料");
				if(a==NULL)
				{
					strcpy(assignWork3,buf);
					assignWork3_valid=1;
					fgets(buf,15010,in);//读入新的
					int len=strlen(buf);
					len--;
					while(isspace(buf[len]))//去掉末尾空白
					{
						len--;
					}
					len++;
					buf[len]='\0';
					a=strstr(buf,"参考资料");
					if(a==NULL)
					{
						strcpy(assignWork4,buf);
						assignWork4_valid=1;
						fgets(buf,15010,in);//读入新的
						int len=strlen(buf);
						len--;
						while(isspace(buf[len]))//去掉末尾空白
						{
							len--;
						}
						len++;
						buf[len]='\0';
						a=strstr(buf,"参考资料");
						if(a==NULL)
						{
							strcpy(assignWork5,buf);
							assignWork5_valid=1;
							fgets(buf,15010,in);//读入新的
							int len=strlen(buf);
							len--;
							while(isspace(buf[len]))//去掉末尾空白
							{
								len--;
							}
							len++;
							buf[len]='\0';
							a=strstr(buf,"参考资料");
							if(a==NULL)
							{
								strcpy(assignWork6,buf);
								assignWork6_valid=1;
								fgets(buf,15010,in);//读入新的
								int len=strlen(buf);
								len--;
								while(isspace(buf[len]))//去掉末尾空白
								{
									len--;
								}
								len++;
								buf[len]='\0';
							}
						}
					}
				}
			}
		}
		fgets(buf,15010,in);//读入新的
		len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
		a=strstr(buf,"学院");
		if(a==NULL)
		{
			strcpy(assignRef1,buf);
			assignRef1_valid=1;
			fgets(buf,15010,in);//读入新的
			int len=strlen(buf);
			len--;
			while(isspace(buf[len]))//去掉末尾空白
			{
				len--;
			}
			len++;
			buf[len]='\0';
			a=strstr(buf,"学院");
			if(a==NULL)
			{
				strcpy(assignRef2,buf);
				assignRef2_valid=1;
				fgets(buf,15010,in);//读入新的
				int len=strlen(buf);
				len--;
				while(isspace(buf[len]))//去掉末尾空白
				{
					len--;
				}
				len++;
				buf[len]='\0';
				a=strstr(buf,"学院");
				if(a==NULL)
				{
					strcpy(assignRef3,buf);
					assignRef3_valid=1;
					fgets(buf,15010,in);//读入新的
					int len=strlen(buf);
					len--;
					while(isspace(buf[len]))//去掉末尾空白
					{
						len--;
					}
					len++;
					buf[len]='\0';
					a=strstr(buf,"学院");
					if(a==NULL)
					{
						strcpy(assignRef4,buf);
						assignRef4_valid=1;
						fgets(buf,15010,in);//读入新的
						int len=strlen(buf);
						len--;
						while(isspace(buf[len]))//去掉末尾空白
						{
							len--;
						}
						len++;
						buf[len]='\0';
						a=strstr(buf,"学院");
						if(a==NULL)
						{
							strcpy(assignRef5,buf);
							assignRef5_valid=1;
							fgets(buf,15010,in);//读入新的
							int len=strlen(buf);
							len--;
							while(isspace(buf[len]))//去掉末尾空白
							{
								len--;
							}
							len++;
							buf[len]='\0';
							a=strstr(buf,"学院");
							if(a==NULL)
							{
								strcpy(assignRef6,buf);
								assignRef6_valid=1;
								fgets(buf,15010,in);//读入新的
								int len=strlen(buf);
								len--;
								while(isspace(buf[len]))//去掉末尾空白
								{
									len--;
								}
								len++;
								buf[len]='\0';
								a=strstr(buf,"学院");
								if(a==NULL)
								{
									strcpy(assignRef7,buf);
									assignRef7_valid=1;
									fgets(buf,15010,in);//读入新的
									int len=strlen(buf);
									len--;
									while(isspace(buf[len]))//去掉末尾空白
									{
										len--;
									}
									len++;
									buf[len]='\0';
									a=strstr(buf,"学院");
									if(a==NULL)
									{
										strcpy(assignRef8,buf);
										assignRef8_valid=1;
										fgets(buf,15010,in);//读入新的
										int len=strlen(buf);
										len--;
										while(isspace(buf[len]))//去掉末尾空白
										{
											len--;
										}
										len++;
										buf[len]='\0';
									}
								}
							}
						}
					}
				}
			}
		}
		return 1;
	}
	a=strstr(buf,"班");
	if(a!=NULL&&class_num_valid!=1)//定位到班一行
	{
		b=strstr(buf,"类");
		b+=strlen("类");
		while(isspace(*b))
		{
			b++;
		}
		strcpy(class_num,b);
		a=strstr(class_num,"班");
		a--;
		while(isspace(*a))//倒着剪裁空格
		{
			a--;
		}
		a++;
		*a='\0';//在这里截断
		class_num_valid=1;
		return 1;
	}
	a=strstr(buf,"毕业设计");
	b=strstr(buf,"论文");
	c=strstr(buf,"时间");
	if(a!=NULL&&b!=NULL&&c!=NULL&&thesisbegin_year_valid!=1)
	{
		c=strstr(buf,"时间：");
		c+=strlen("时间：");
		while(isspace(*c))
		{
			c++;
		}
		strcpy(thesisbegin_year,c);//年从这起始
		a=strstr(thesisbegin_year,"年");//定位
		b=a;//同时定位月的起始
		b+=strlen("年");//b指向后半部分
		while(isspace(*b))
		{
			b++;
		}
		strcpy(thesisbegin_month,b);//必须提前搬运，月从这起始
		a--;
		while(isspace(*a))//倒着剪裁空格
		{
			a--;
		}
		a++;
		*a='\0';//在这里截断
		thesisbegin_year_valid=1;//年处理完成
		c=strstr(thesisbegin_month,"月");//定位
		a=c;//同时定位日的起始
		a+=strlen("月");//a指向后半部分
		while(isspace(*a))
		{
			a++;
		}
		strcpy(thesisbegin_date,a);//必须提前搬运，日从这起始
		c--;
		while(isspace(*c))//倒着剪裁空格
		{
			c--;
		}
		c++;
		*c='\0';//在这里截断
		thesisbegin_month_valid=1;//月处理完成
		b=strstr(thesisbegin_date,"日至");//定位
		c=b;//同时定位年的起始
		c+=strlen("日至");//c指向后半部分
		while(isspace(*c))
		{
			c++;
		}
		strcpy(thesisend_year,c);//必须提前搬运，年从这起始
		b--;
		while(isspace(*b))//倒着剪裁空格
		{
			b--;
		}
		b++;
		*b='\0';//在这里截断
		thesisbegin_date_valid=1;//日处理完成
		a=strstr(thesisend_year,"年");//定位
		b=a;//同时定位月的起始
		b+=strlen("年");//b指向后半部分
		while(isspace(*c))
		{
			c++;
		}
		strcpy(thesisend_month,c);//必须提前搬运，月从这起始
		a--;
		while(isspace(*a))//倒着剪裁空格
		{
			a--;
		}
		a++;
		*a='\0';//在这里截断
		thesisend_year_valid=1;//年处理完成
		c=strstr(thesisend_month,"月");//定位
		a=c;//同时定位日的起始
		a+=strlen("月");//a指向后半部分
		while(isspace(*a))
		{
			a++;
		}
		strcpy(thesisend_date,a);//必须提前搬运，日从这起始
		c--;
		while(isspace(*c))//倒着剪裁空格
		{
			c--;
		}
		c++;
		*c='\0';//在这里截断
		thesisend_month_valid=1;//月处理完成
		b=strstr(thesisend_date,"日");//定位
		b--;
		while(isspace(*b))//倒着剪裁空格
		{
			b--;
		}
		b++;
		*b='\0';//在这里截断
		thesisend_date_valid=1;//日处理完成
		return 1;
	}
	a=strstr(buf,"答辩");
	b=strstr(buf,"时间");
	if(a!=NULL&&b!=NULL&&defense_year_valid!=1)
	{
		c=strstr(buf,"时间：");
		c+=strlen("时间：");
		while(isspace(*c))
		{
			c++;
		}
		strcpy(defense_year,c);//年从这起始
		a=strstr(defense_year,"年");//定位
		b=a;//同时定位月的起始
		b+=strlen("年");//b指向后半部分
		while(isspace(*b))
		{
			b++;
		}
		strcpy(defense_month,b);//提前搬运，月从这起始
		a--;
		while(isspace(*a))//倒着剪裁空格
		{
			a--;
		}
		a++;
		*a='\0';//在这里截断
		defense_year_valid=1;//年处理完成
		c=strstr(defense_month,"月");//定位
		a=c;//同时定位日的起始
		a+=strlen("月");//a指向后半部分
		while(isspace(*a))
		{
			a++;
		}
		strcpy(defense_date,a);//提前搬运，日从这起始
		c--;
		while(isspace(*c))//倒着剪裁空格
		{
			c--;
		}
		c++;
		*c='\0';//在这里截断
		defense_month_valid=1;//月处理完成
		b=strstr(defense_date,"日");//定位
		b--;
		while(isspace(*b))//倒着剪裁空格
		{
			b--;
		}
		b++;
		*b='\0';//在这里截断
		defense_date_valid=1;//日处理完成
	}
	a=strstr(buf,"北京航空航天大学毕业设计");
	b=strstr(buf,"I");//摘要是第I页
	if(a!=NULL&&b!=NULL&&title_ch_valid!=1)
	{
		fgets(buf,15010,in);//重新读入一遍
		int len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
		strcpy(title_ch,buf);//标题
		title_ch_valid=1;
		fgets(buf,15010,in);//重新读入一遍
		len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
		strcpy(subtitle_ch,buf);//副标题
		subtitle_ch_valid=1;
		return 1;
	}
	a=strstr(buf,"摘");
	b=strstr(buf,"要");//从这里开始是摘要和关键词
	if(a!=NULL&&b!=NULL&&abstract_ch_valid!=1)
	{
		fgets(buf,15010,in);//重新读入一遍
		int len=strlen(buf);
		len--;
		while(isspace(buf[len])&&buf[len]!='\n')//去掉末尾空白，但这里换行除外
		{
			len--;
		}
		len++;
		a=strstr(buf,"关键词");
		while(a==NULL)
		{
			printf("success!");
			strcat(abstract_ch,buf);//直接接上去
			fgets(buf,15010,in);//重新读入一遍
			int len=strlen(buf);
			len--;
			while(isspace(buf[len])&&buf[len]!='\n')//去掉末尾空白，但这里换行除外
			{
				len--;
			}
			len++;
			a=strstr(buf,"关键词");
		}
		abstract_ch_valid=1;//摘要
		len=strlen(buf);//关键词行，重新裁剪
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
		a=strstr(buf,"关键词：");
		a+=strlen("关键词：");
		while(isspace(*a))
		{
			a++;
		}
		strcpy(keyword_ch,a);//关键词
		keyword_ch_valid=1;
		return 1;
	}
	a=strstr(buf,"北京航空航天大学毕业设计");
	b=strstr(buf,"II");//摘要是第I页
	if(a!=NULL&&b!=NULL&&title_en_valid!=1)
	{
		fgets(buf,15010,in);//重新读入一遍
		int len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
		strcpy(title_en,buf);//标题
		title_en_valid=1;
		fgets(buf,15010,in);//重新读入一遍
		len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
		strcpy(subtitle_en,buf);//副标题
		subtitle_en_valid=1;
		return 1;
	}
	a=strstr(buf,"Author");
	if(a!=NULL&&author_en_valid!=1)
	{
		a=strstr(buf,"Author:");
		a+=strlen("Author:");
		while(isspace(*a))
		{
			a++;
		}
		strcpy(author_en,a);
		author_en_valid=1;
		return 1;
	}
	a=strstr(buf,"Tutor");
	if(a!=NULL&&teacher_en_valid!=1)
	{
		a=strstr(buf,"Tutor:");
		a+=strlen("Tutor:");
		while(isspace(*a))
		{
			a++;
		}
		strcpy(teacher_en,a);
		teacher_en_valid=1;
		return 1;
	}
	a=strstr(buf,"Abstract");//从这里开始是摘要和关键词
	if(a!=NULL&&abstract_en_valid!=1)
	{
		fgets(buf,15010,in);//重新读入一遍
		int len=strlen(buf);
		len--;
		while(isspace(buf[len])&&buf[len]!='\n')//去掉末尾空白，但这里换行除外
		{
			len--;
		}
		len++;
		a=strstr(buf,"Key");
		b=strstr(buf,"words");
		while(a==NULL||b==NULL)
		{
			strcat(abstract_en,buf);//直接接上去
			fgets(buf,15010,in);//重新读入一遍
			int len=strlen(buf);
			len--;
			while(isspace(buf[len])&&buf[len]!='\n')//去掉末尾空白，但这里换行除外
			{
				len--;
			}
			len++;
			a=strstr(buf,"Key");
			b=strstr(buf,"words");
		}
		abstract_en_valid=1;//摘要
		len=strlen(buf);//关键词行，重新裁剪
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
		b=strstr(buf,"words:");
		b+=strlen("words:");
		while(isspace(*b))
		{
			b++;
		}
		strcpy(keyword_en,b);//关键词
		keyword_en_valid=1;
		return 1;
	}
	a=strstr(buf,"目");//定位结束
	b=strstr(buf,"录");
	if(a!=NULL&&b!=NULL)
	{
		return -1;
	}
}

void print_cover()//逐步输出文件
{
	printf("OK2\n");
	fprintf(out,"%% !Mode:: \"TeX:UTF-8\"\n");
	fprintf(out,"\\unicode{10006}\n");
	fprintf(out,"\\studentID{%s}\n",studentID);//学号
	fprintf(out,"\\category{%s}\n",category);//中图分类号
	fprintf(out,"\\thesistitle\n");
	fprintf(out,"{%s}\n",title_ch);//中文标题
	fprintf(out,"{%s}\n",subtitle_ch);//中文副标题
	fprintf(out,"{%s}\n",title_en);//英文标题
	fprintf(out,"{%s}\n",subtitle_en);//英文副标题
	fprintf(out,"\\school{%s}{}\n",school);//学院名
	fprintf(out,"\\major{%s}{}\n",major);//专业名
	fprintf(out,"\\thesisauthor{%s}{%s}\n",author_ch,author_en);//作者名
	fprintf(out,"\\teacher{%s}{%s}\n",teacher_ch,teacher_en);//导师名
	fprintf(out,"\\thesisdate{%s}{%s}\n",thesisdate_year,thesisdate_month);//论文时间
	fprintf(out,"\\assignReq\n");
	fprintf(out,"{%s}\n",assignReq1);//原始资料及设计1
	fprintf(out,"{%s}\n",assignReq2);//原始资料及设计2
	fprintf(out,"{%s}\n",assignReq3);//原始资料及设计3
	fprintf(out,"{%s}\n",assignReq4);//原始资料及设计4
	fprintf(out,"{%s}\n",assignReq5);//原始资料及设计5
	fprintf(out,"\\assignWork\n");
	fprintf(out,"{%s}\n",assignWork1);//工作内容1
	fprintf(out,"{%s}\n",assignWork2);//工作内容2
	fprintf(out,"{%s}\n",assignWork3);//工作内容3
	fprintf(out,"{%s}\n",assignWork4);//工作内容4
	fprintf(out,"{%s}\n",assignWork5);//工作内容5
	fprintf(out,"{%s}\n",assignWork6);//工作内容6
	fprintf(out,"\\assignRef\n");
	fprintf(out,"{%s}\n",assignRef1);//参考文献1
	fprintf(out,"{%s}\n",assignRef2);//参考文献2
	fprintf(out,"{%s}\n",assignRef3);//参考文献3
	fprintf(out,"{%s}\n",assignRef4);//参考文献4
	fprintf(out,"{%s}\n",assignRef5);//参考文献5
	fprintf(out,"{%s}\n",assignRef6);//参考文献6
	fprintf(out,"{%s}\n",assignRef7);//参考文献7
	fprintf(out,"{%s}\n",assignRef8);//参考文献8
	fprintf(out,"\\class{%s}\n",class_num);//班级号
	fprintf(out,"\\thesisbegin{%s}{%s}{%s}\n",thesisbegin_year,thesisbegin_month,thesisbegin_date);//毕设开始时间
	fprintf(out,"\\thesisend{%s}{%s}{%s}\n",thesisend_year,thesisend_month,thesisend_date);//毕设结束时间
	fprintf(out,"\\defense{%s}{%s}{%s}\n",defense_year,defense_month,defense_date);//毕设答辩时间
	fprintf(out,"\\pagestyle{mainmatter}\n");
	fprintf(out,"\\maketitle\n");
	fprintf(out,"\\begin{cabstract}\n");
	fprintf(out,"%s\n",abstract_ch);//中文摘要
	fprintf(out,"\\end{cabstract}\n");
	fprintf(out,"\\ckeyword{%s}\n",keyword_ch);//中文关键词
	fprintf(out,"\\begin{eabstract}\n");
	fprintf(out,"%s\n",abstract_en);//英文摘要
	fprintf(out,"\\end{eabstract}\n");
	fprintf(out,"\\ekeyword{%s}\n",keyword_en);//英文关键词
}

void process_cover()//处理开头——为了定位，这部分页眉要特判
{
	fgets(buf,15010,in);//读入第一行
	int len=strlen(buf);
	len--;
	while(isspace(buf[len]))//去掉末尾空白
	{
		len--;
	}
	len++;
	buf[len]='\0';
	while(checkcover()!=-1)//checkcover没结束
	{
		fgets(buf,15010,in);//读入新的行
		int len=strlen(buf);
		len--;
		while(isspace(buf[len]))//去掉末尾空白
		{
			len--;
		}
		len++;
		buf[len]='\0';
	}
	print_cover();//输出cover
}

int main()
{
	in=fopen("in.txt","r");
	out=fopen("1cover.tex","w");//打开cover。这部分要全读完再统一输出，输入和输出分离
	process_cover();
	fclose(out);//关闭cover
	out=fopen("2text.tex","w");//打开text
	checkbegin();//执行结束后，这一行里拥有绪论——这个功能本来应该在上一部分
	process_text();//边读入边输出
	fclose(out);//关闭text
	out=fopen("3conclusion.tex","w");//打开conclusion。此时这一行拥有结论二字
	process_conclusion();//结论部分——待完成
	fclose(out);//关闭conclusion
	out=fopen("4bibs.bib","w");//打开bibs
	printbibs();
	fclose(out);//关闭bibs
	out=fopen("5appendix.tex","w");//打开appendix
	checkappbegin();//执行结束后，这一行里拥有附录——这个功能本来应该在上一部分
	process_appendix();//附录部分——待完成
	fclose(out);//关闭appendix
	fclose(in);
}

