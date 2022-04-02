#include<stdio.h>
#include<string.h>

FILE *in;//输入
FILE *out;//输出
char buf[20010];//输入输出

char studentID[35];//学号
int studentID_valid;
char category[35];//中图分类号，http://www.ztflh.com/
int category_valid;
char title_ch[35];//中文标题
int title_ch_valid;
char subtitle_ch[35];//中文副标题
int subtitle_ch_valid;
char title_en[35];//英文标题
char subtitle_en[35];//英文副标题
char school[35];//学院名
int school_valid;
char major[35];//专业名
int major_valid;
char author_ch[35];//作者名中文
int author_ch_valid;
char author_en[35];//作者名英文
char teacher_ch[35];//导师名中文
int teacher_ch_valid;
char teacher_en[35];//导师名英文
char thesisdate_year[35];//论文时间年
int thesisdate_year_valid;
char thesisdate_month[35];//论文时间月
int thesisdate_month_valid;
char assignReq1[60];//原始资料及设计1
char assignReq2[60];//原始资料及设计2
char assignReq3[60];//原始资料及设计3
char assignReq4[60];//原始资料及设计4
char assignReq5[60];//原始资料及设计5
char assignWork1[60];//工作内容1
char assignWork2[60];//工作内容2
char assignWork3[60];//工作内容3
char assignWork4[60];//工作内容4
char assignWork5[60];//工作内容5
char assignWork6[60];//工作内容6
char assignRef1[60];//参考文献1
char assignRef2[60];//参考文献2
char assignRef3[60];//参考文献3
char assignRef4[60];//参考文献4
char assignRef5[60];//参考文献5
char assignRef6[60];//参考文献6
char assignRef7[60];//参考文献7
char assignRef8[60];//参考文献8
char class_num[35];//班级号
char thesisbegin_year[35];//毕设开始时间年
char thesisbegin_month[35];//毕设开始时间月
char thesisbegin_date[35];//毕设开始时间日
char thesisend_year[35];//毕设开始时间年
char thesisend_month[35];//毕设开始时间月
char thesisend_date[35];//毕设开始时间日
char defense_year[35];//毕设开始时间年
char defense_month[35];//毕设开始时间月
char defense_date[35];//毕设开始时间日
char abstract_ch[2010];//中文摘要
char keyword_ch[210];//中文关键词
char abstract_en[2010];//英文摘要
char keyword_en[210];//英文关键词

void print_cover()
{
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

int checkcover()
{
	char *a=strstr(buf,"学号");
	if(a!=NULL&&studentID_valid!=1)
	{
		a+=strlen("学号");
		strcpy(studentID,a);
		studentID_valid=1;
		return 1;
	}
	a=strstr(buf,"分类号");
	if(a!=NULL&&category_valid!=1)
	{
		a+=strlen("分类号");
		strcpy(category,a);
		category_valid=1;
		return 1;
	}
	a=strstr(buf,"毕业设计(论文)");
	if(a!=NULL&&title_ch_valid!=1&&subtitle_ch_valid!=1)
	{
		fgets(buf,20010,in);//读入新的
		strcpy(title_ch,buf);//标题
		title_ch_valid=1;
		fgets(buf,20010,in);//读入新的
		strcpy(subtitle_ch,buf);//副标题
		subtitle_ch_valid=1;
		return 1;
	}
	a=strstr(buf,"学院名称");
	if(a!=NULL&&school_valid!=1)
	{
		a+=strlen("学院名称");
		strcpy(school,a);
		a=school;
		a+=strlen(school);
		a-=strlen("学院");
		*a='\0';
		school_valid=1;
		return 1;
	}
	a=strstr(buf,"专业名称");
	if(a!=NULL&&major_valid!=1)
	{
		a+=strlen("专业名称");
		strcpy(major,a);
		a=major;
		a+=strlen(major);
		a-=strlen("专业");
		*a='\0';
		major_valid=1;
		return 1;
	}
	a=strstr(buf,"学生姓名");
	if(a!=NULL&&author_ch_valid!=1)
	{
		a+=strlen("学生姓名");
		strcpy(author_ch,a);
		author_ch_valid=1;
		return 1;
	}
	a=strstr(buf,"指导教师");
	if(a!=NULL&&teacher_ch_valid!=1)
	{
		a+=strlen("指导教师");
		strcpy(teacher_ch,a);
		teacher_ch_valid=1;
		return 1;
	}
	a=strstr(buf,"年");
	if(a!=NULL&&thesisdate_year_valid!=1)
	{
		strcpy(thesisdate_year,buf);
		a=thesisdate_year;
		a+=strlen(thesisdate_year);
		a-=strlen("年");
		*a='\0';
		thesisdate_year_valid=1;
		return 1;
	}
	
	return -1;//-1表示结束
}

int main()
{
	in=fopen("in.txt","r");
	out=fopen("1cover.tex","w");//打开cover
	fgets(buf,20010,in);//读入第一行
	while(checkcover()!=-1)//没结束
	{
		fgets(buf,20010,in);//读入新的
	}
	print_cover();
	fclose(out);//关闭cover
	out=fopen("2text.tex","w");//打开text
	
	
	fclose(out);//关闭text
	out=fopen("3conclusion.tex","w");//打开conclusion
	
	
	fclose(out);//关闭conclusion
	out=fopen("4bibs.bib","w");//打开bibs
	
	
	fclose(out);//关闭bibs
	out=fopen("5appendix.tex","w");//打开appendix
	
	
	fclose(out);//关闭appendix
	fclose(in);
}