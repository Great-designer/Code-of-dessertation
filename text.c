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

//阶段性胜利！这边去上传一下GitHub

int main()
{
	in=fopen("in.txt","r");
//	out=fopen("1cover.tex","w");//打开cover
//	readline();//读入第一行
//	while(checkcover()!=-1)//没结束
//	{
//		readline();//读入新的
//	}
//	print_cover();
//	fclose(out);//关闭cover
	out=fopen("2text.tex","w");//打开text
	checkbegin();//执行结束后，这一行里拥有绪论——这个功能本来应该在上一部分
	process_text();//边读入边输出
	fclose(out);//关闭text
	out=fopen("3conclusion.tex","w");//打开conclusion。此时这一行拥有结论二字
	process_conclusion();//结论部分——待完成
	fclose(out);//关闭conclusion
//	out=fopen("4bibs.bib","w");//打开bibs……这个功能去了吧
//	printbibs();
//	fclose(out);//关闭bibs
	out=fopen("5appendix.tex","w");//打开appendix
	checkappbegin();//执行结束后，这一行里拥有附录——这个功能本来应该在上一部分
	process_appendix();//附录部分——待完成
	fclose(out);//关闭appendix
	fclose(in);
}

