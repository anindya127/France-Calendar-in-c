//This is a skeleton calendar with simple GUI.
//This calendar is based on "France Calender" with real public holiday of France.
// information source "https://en.wikipedia.org/wiki/Public_holidays_in_France" .

//Declare all library.
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<math.h>

//Declare all function.
int gaussEaster(int DD, int MM, int Y);
int gaussAscension(int Dd, int Mm, int Yy);
int gaussWhitMonday(int Day, int Month, int Year);
int allholidaysinFrance(int days, int monthss);
unsigned day_of_week( unsigned year, unsigned month, unsigned day );
int monthday(int mm,int yy);
int leepyear(int yearn);
void dayindicator(int Dayx, int Monthx, int Yearx);
void calendar(int year);
void dayofthedate(int xday, int xmonth, int xyear);
void onlyonemonthcalendar(int Mmonth, int Yyear);
void allmonth(int m,int y);
int get1stweekday(int yer);

int main()//main function.
{
    system("color F0");//color the console as white as background and black as foreground.
    COORD c;
    c.X = 50;
    c.Y = 1;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);//print the text in center{only work for one line.}.

    printf("France Calendar\n");
    int d,m,y,i,n;
    //printf("Press 1 for full Calender of a year. \nPress 2 for a month Calender of year. \nPress 0 to exit. \nYou Press : ");
    for(i=1;;i++)
    {
        printf("\n\nPress 1 for full Calender of a year. \nPress 2 for a month Calender of year. \nPress 3 get the day of the date and indicate it on calendar. \nPress 0 to exit. \nYou Press : ");
        scanf("%d",&n);
        if(n==1)
        {
            printf("\nEnter the Year : ");
            scanf("%d",&y);
            calendar(y);
        }
        else if(n==2)
        {
            printf("\nEnter the Month and Year as : (MM YYYY) : ");
            scanf("%d %d",&m,&y);
            onlyonemonthcalendar(m,y);
        }
        else if(n==3)
        {
            printf("\nEnter the date as : (DD MM YYYY) : ");
            scanf("%d %d %d",&d ,&m,&y);
            dayofthedate(d,m,y);
            dayindicator(d,m,y);
        }
        else if(n==0)
        {
            break;
        }
        else
        {
            printf("Error 404!!");
        }
    }
    return 0;
}

int leepyear(int yearn)//check the year is leap year or not. yearn = year.
{
    return (yearn%4==0&&yearn%100!=0||yearn%400==0);
}

unsigned day_of_week( unsigned year, unsigned month, unsigned day )//algorithm for get day of a date.
{
  unsigned a, y, m;
  a = (14 - month) / 12;
  y = year - a;
  m = month + (12 * a) - 2;
  // Gregorian:
  return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;//here 0 = Sunday, 1 = Monday, 2 =  Tuesday, 3= Wednesday, 4 =Thursday, 5 =  Friday, 6 = Saturday.
}

void dayofthedate(int xday, int xmonth, int xyear)//get the day of any given date.
{
    int x;
    x=day_of_week(xyear,xmonth,xday);
    if(x==0)
    {
        printf("\nWeekday = Sunday");
    }
    else if(x==1)
    {
        printf("\nWeekday = Monday");
    }
    else if(x==2)
    {
        printf("\nWeekday = Tuesday");
    }
    else if(x==3)
    {
        printf("\nWeekday = Wednesday");
    }
    else if(x==4)
    {
        printf("\nWeekday = Thursday");
    }
    else if(x==5)
    {
        printf("\nWeekday = Friday");
    }
    else if(x==6)
    {
        printf("\nWeekday = Saturday");
    }
}

void dayindicator(int Dayx, int Monthx, int Yearx)//indicate the given date. DAyx = day. Monthx = month, Yearx = year.
{
    int month,day,days_In_a_Month,weekDay=0,startingDay;
    allmonth(Monthx,Yearx);
    days_In_a_Month=monthday(Monthx,Yearx);
    startingDay=day_of_week(Yearx,Monthx,1);//get the 1st day of any given month.
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hc, 0xF4);//color foreground as red and background white.weekend day are color red.
    printf("Su");
    SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
    printf (" Mo Tu We Th Fr ");
    SetConsoleTextAttribute(hc, 0xF4);//color foreground as red and background white.weekend day are color red.
    printf("Sa\n\n");
    SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
    for(weekDay=0;weekDay<startingDay;weekDay++)
    {
        printf("   ");
    }
    for(day=1;day<=days_In_a_Month;day++)
    {
        if(gaussEaster(day,Monthx,Yearx) && day==Dayx)
        {
            SetConsoleTextAttribute(hc, 0x02);//color foreground as green and background black.public holiday.ester Sunday.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(gaussEaster(day+2,Monthx,Yearx) && day==Dayx)
        {
            SetConsoleTextAttribute(hc, 0x02);//color foreground as green and background black. public holiday. Good Friday.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0x0F);//color foreground as black and background white.
        }
        else if(gaussAscension(day,Monthx,Yearx) && day==Dayx)
        {
            SetConsoleTextAttribute(hc, 0x02);//color foreground as green and background black.public holiday. Ascension day.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(gaussWhitMonday(day,Monthx,Yearx) && day==Dayx)
        {
            SetConsoleTextAttribute(hc, 0x02);//color foreground as green and background black.public holiday. Whit Monday.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(gaussEaster(day-1,Monthx,Yearx) && day==Dayx)
        {
            SetConsoleTextAttribute(hc, 0x02);//color foreground as green and background black.public holiday.ester Monday.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(allholidaysinFrance(day,Monthx) && day==Dayx)
        {
            SetConsoleTextAttribute(hc, 0x02);//color foreground as green and background black. all public holiday with a fixed date.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(weekDay==0 && day==Dayx||weekDay==6 && day==Dayx)
        {
            SetConsoleTextAttribute(hc, 0x04);//color foreground as red and background black.Weekend are color red.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(day==Dayx)
        {
            SetConsoleTextAttribute(hc, 0x0F);//color foreground as white and background black.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(gaussEaster(day,Monthx,Yearx))
        {
            SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white.public holiday.ester Sunday.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(gaussEaster(day+2,Monthx,Yearx))
        {
            SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white. public holiday. Good Friday.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(gaussAscension(day,Monthx,Yearx))
        {
            SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white.public holiday. Ascension day.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(gaussWhitMonday(day,Monthx,Yearx))
        {
            SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white.public holiday. Whit Monday.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(gaussEaster(day-1,Monthx,Yearx))
        {
            SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white.public holiday.ester Monday.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(allholidaysinFrance(day,Monthx))
        {
            SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white. all public holiday with a fixed date.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(weekDay==0||weekDay==6)
        {
            SetConsoleTextAttribute(hc, 0xF4);//color foreground as red and background white.Weekend are color red.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else
        {
            printf("%2d ",day);
        }
        weekDay++;
        if(weekDay>6)
        {
            printf("\n");
            weekDay=0;
        }
        startingDay=weekDay;
    }
}

void onlyonemonthcalendar(int Mmonth, int Yyear)//only get the calendar for one month. Mmonth = month, Yyear = year.
{
    int month,day,days_In_a_Month,weekDay=0,startingDay;
    allmonth(Mmonth,Yyear);
    days_In_a_Month=monthday(Mmonth,Yyear);
    startingDay=day_of_week(Yyear,Mmonth,1);//get the 1st day of any given month.
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hc, 0xF4);//color foreground as red and background white.weekend day are color red.
    printf("Su");
    SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
    printf (" Mo Tu We Th Fr ");
    SetConsoleTextAttribute(hc, 0xF4);//color foreground as red and background white.weekend day are color red.
    printf("Sa\n\n");
    SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
    for(weekDay=0;weekDay<startingDay;weekDay++)
    {
        printf("   ");
    }
    for(day=1;day<=days_In_a_Month;day++)
    {
        if(gaussEaster(day,Mmonth,Yyear))
        {
            SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white.public holiday.ester Sunday.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(gaussEaster(day+2,Mmonth,Yyear))
        {
            SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white. public holiday. Good Friday.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(gaussAscension(day,Mmonth,Yyear))
        {
            SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white.public holiday. Ascension day.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(gaussWhitMonday(day,Mmonth,Yyear))
        {
            SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white.public holiday. Whit Monday.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(gaussEaster(day-1,Mmonth,Yyear))
        {
            SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white.public holiday.ester Monday.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(allholidaysinFrance(day,Mmonth))
        {
            SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white. all public holiday with a fixed date.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else if(weekDay==0||weekDay==6)
        {
            SetConsoleTextAttribute(hc, 0xF4);//color foreground as red and background white.Weekend are color red.
            printf("%2d ",day);
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
        }
        else
        {
            printf("%2d ",day);
        }
        weekDay++;
        if(weekDay>6)
        {
            printf("\n");
            weekDay=0;
        }
        startingDay=weekDay;
    }
}

void calendar(int year)//main calendar container.color red = weekend. color green = public holiday.if a day is weekend and it's a public holiday it will show in green.
{
    int month,day,days_In_a_Month,weekDay=0,startingDay;
    startingDay=get1stweekday(year);//get 1st of a year.
    for(month=1;month<=12;month++)
        {
            allmonth(month,year);
            days_In_a_Month=monthday(month,year);
            HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hc, 0xF4);//color foreground as red and background white.weekend day are color red.
            printf("Su");
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
            printf (" Mo Tu We Th Fr ");
            SetConsoleTextAttribute(hc, 0xF4);//color foreground as red and background white.weekend day are color red.
            printf("Sa\n\n");
            SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
            for(weekDay=0;weekDay<startingDay;weekDay++)
            {
                printf("   ");
            }
            for(day=1;day<=days_In_a_Month;day++)
            {
                if(gaussEaster(day,month,year))
                {
                    SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white.public holiday.ester Sunday.
                    printf("%2d ",day);
                    SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
                }
                else if(gaussEaster(day+2,month,year))
                {
                    SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white. public holiday. Good Friday.
                    printf("%2d ",day);
                    SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
                }
                else if(gaussAscension(day,month,year))
                {
                    SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white.public holiday. Ascension day.
                    printf("%2d ",day);
                    SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
                }
                else if(gaussWhitMonday(day,month,year))
                {
                    SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white.public holiday. Whit Monday.
                    printf("%2d ",day);
                    SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
                }
                else if(gaussEaster(day-1,month,year))
                {
                    SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white.public holiday.ester Monday.
                    printf("%2d ",day);
                    SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
                }
                else if(allholidaysinFrance(day,month))
                {
                    SetConsoleTextAttribute(hc, 0xF2);//color foreground as green and background white. all public holiday with a fixed date.
                    printf("%2d ",day);
                    SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
                }
                else if(weekDay==0||weekDay==6)
                {
                    SetConsoleTextAttribute(hc, 0xF4);//color foreground as red and background white.Weekend are color red.
                    printf("%2d ",day);
                    SetConsoleTextAttribute(hc, 0xF0);//color foreground as black and background white.
                }
                else
                    {
                        printf("%2d ",day);
                    }
                weekDay++;
                if(weekDay>6)
                {
                    printf("\n");
                    weekDay=0;
                }
                startingDay=weekDay;
            }
        }
}

void allmonth(int m,int y)//contain the name of all month.
//m= month number, y= year
{
    char *monthsname[]={"\0","January","February","March","April","May","June","July","August","September","October","November","December"};
    printf ("\n\n    %s %d    \n",monthsname[m],y);
}

int monthday(int mm,int yy)//contain how many days all the month has.
//mm=month, yy=year
{
    int monthDay[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(leepyear(yy))
    {
        monthDay[2]=29;
    }
    return monthDay[mm];
}

int get1stweekday(int yer)//get 1st day of year. yer = year.
{
    int dday;
    dday=(((yer-1)*365)+((yer-1)/4)-((yer-1)/100)+((yer)/400)+1)%7;//here 0 = Sunday, 1 = Monday, 2 =  Tuesday, 3= Wednesday, 4 =Thursday, 5 =  Friday, 6 = Saturday.
    return dday;
}

int allholidaysinFrance(int days, int monthss)//All holiday that are not changeable.
{
    return (monthss==1&&days==1||monthss==3&&days==1||monthss==3&&days==8||monthss==7&&days==14||monthss==8&&days==15||monthss==11&&days==1||monthss==11&&days==11||monthss==12&&days==25||monthss==12&&days==26);
}

int gaussEaster(int DD, int MM, int Y)//get ester Sunday.DD = day. MM = month. Y = year.
{
    float A, B, C, P, Q, M, N, D, E;

    // All calculations done
    // on the basis of
    // Gauss Easter Algorithm
    A = Y % 19;//calculate the location of the year Y in the Metonic cycle.
    B = Y % 4;//find the number of leap days according to Julian’s calendar.
    C = Y % 7;//let’s take into account that the non-leap year is one day longer than 52 weeks.
    P = (float)floor(Y / 100);
    Q = (float)floor((13 + 8 * P) / 25);
    M = (int)(15 - Q + P - P / 4) % 30;//M depends on the century of year Y. For 19th century, M = 23. For the 21st century, M = 24 and so on.
    N = (int)(4 + P - P / 4) % 7;//The difference between the number of leap days between the Julian and the Gregorian calendar.
    D = (int)(19 * A + M) % 30;//The number of days to be added to March 21 to find the date of the Paschal Full Moon.
    E = (int)(2 * B + 4 * C + 6 * D + N) % 7;//the number of days from the Paschal full moon to the next Sunday.
    int days = (int)(22 + D + E);
    if(D==29 && E==6)
    {
        // A corner case,
        // when D is 29
        return(MM==4 && DD==19);
    }
    else if(D==28 && E==6)
    {
        // Another corner case,
        // when D is 28
        return(MM==4 && DD==18);
    }
    else
    {
        if(days>31)
        {
            // If days > 31, move to April
            // April = 4th Month
            return(MM==4 && DD==(days-31));
        }
        else
        {
            // Otherwise, stay on March
            // March = 3rd Month
            return(MM==3 && DD==days);
        }
    }
}

int gaussAscension(int Dd, int Mm, int Yy)//get Ascension Day. Dd = day. Mm = month. Yy = year.
{
    float A, B, C, P, Q, M, N, D, E;

    A = Yy % 19;
    B = Yy % 4;
    C = Yy % 7;
    P = (float)floor(Yy / 100);
    Q = (float)floor((13 + 8 * P) / 25);
    M = (int)(15 - Q + P - P / 4) % 30;
    N = (int)(4 + P - P / 4) % 7;
    D = (int)(19 * A + M) % 30;
    E = (int)(2 * B + 4 * C + 6 * D + N) % 7;
    int days = (int)(22 + D + E);
    if(D==29 && E==6)
    {
        return(Mm==5 && Dd==28);//because the ester is on April 19 so after 39 day we got the Ascension Day on 28th may.39-(30-19)=28.
    }
    else if(D==28 && E==6)
    {
        return(Mm==5 && Dd==27);//because the ester is on April 18 so after 39 day we got the Ascension Day on 27th may.39-(30-18)=27.
    }
    else
    {
        if(days>31)
        {
            return(Mm==5 && Dd==39-(30-(days-31)));//algorithm to get the date for Ascension Day if the ester Sunday is on April.
        }
        else
        {
            return(Mm==4 && Dd==(39-(31-days)));//algorithm to get the date for Ascension Day if the ester Sunday is on March.
        }
    }
}


int gaussWhitMonday(int Day, int Month, int Year)//get Whit Monday
{
    float A, B, C, P, Q, M, N, D, E;

    A = Year % 19;
    B = Year % 4;
    C = Year % 7;
    P = (float)floor(Year / 100);
    Q = (float)floor((13 + 8 * P) / 25);
    M = (int)(15 - Q + P - P / 4) % 30;
    N = (int)(4 + P - P / 4) % 7;
    D = (int)(19 * A + M) % 30;
    E = (int)(2 * B + 4 * C + 6 * D + N) % 7;
    int days = (int)(22 + D + E);
    if(D==29 && E==6)
    {
        return(Month==6 && Day==8);//because the ester is on April 19 so after 50 day we got the Whit Monday on 8th jun.50-(30-19)-31=8.
    }
    else if(D==28 && E==6)
    {
        return(Month==6 && Day==7);//because the ester is on April 18 so after 50 day we got the Whit Monday on 7th jun.50-(30-18)-31=7.
    }
    else
    {
        if(days>31)
        {
            if(days-31<=11)
            {
                return(Month==5 && Day==50-(30-(days-31)));//algorithm to get the date for Whit Monday if the ester Sunday is on April.
            }
            else
            {
                return(Month==6 && Day==50-(30-(days-31))-31);//algorithm to get the date Whit Monday if the ester Sunday is on April.
            }
        }
        else
        {
            if(days<=11)
            {
                return(Month==4 && Day==(50-(31-days)));//algorithm to get the date for Whit Monday if the ester Sunday is on March.
            }
            else
            {
                return(Month==5 && Day==(50-(31-days))-30);//algorithm to get the date for Whit Monday if the ester Sunday is on March.
            }
        }
    }
}
