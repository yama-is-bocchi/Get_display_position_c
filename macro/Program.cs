
using static System.Collections.Specialized.BitVector32;
using System;
using System.Drawing;
using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using System.Runtime.InteropServices;
using AngleSharp.Html.Dom.Events;
using AngleSharp.Dom;
using System.Text;
using System.Runtime.CompilerServices;
using static System.Net.Mime.MediaTypeNames;
using System.Text.Json.Serialization;
using System.Xml.Linq;
using System.Windows;
using System.Diagnostics;
using System.Windows.Forms;
using Microsoft.VisualBasic.ApplicationServices;
using static System.Windows.Forms.DataFormats;
using System.Text.RegularExpressions;

var Driver = new ChromeDriver();

string phone = "";//Xのアカウントの電話番号
string pass = "";//Xのアカウントのパスワード
List<string> learn_list = new List<string>();
string keycode;
int att_num = 0;
main();


void main()
{
    //ウィンドウサイズと位置を調整
    Driver.Manage().Window.Size = new Size(600, 800);

    Driver.Manage().Window.Position = new Point(1300, 40);

    Driver.Navigate().GoToUrl("https://twitter.com/i/flow/login");

    Thread.Sleep(2000);

    Driver.FindElement(By.Name("text")).SendKeys(phone);

    Thread.Sleep(300);
    //電話番号を入力
    Driver.FindElement(By.XPath(@"//*[@class='css-175oi2r r-sdzlij r-1phboty r-rs99b7 r-lrvibr r-ywje51 r-usiww2 r-13qz1uu r-2yi16 r-1qi8awa r-ymttw5 r-1loqt21 r-o7ynqc r-6416eg r-1ny4l3l']")).Click();
    Thread.Sleep(1000);

    Driver.FindElement(By.Name("password")).SendKeys(pass);

    Thread.Sleep(300);
    //パスワードを入力
    Driver.FindElement(By.XPath(@"//*[@class='css-175oi2r r-sdzlij r-1phboty r-rs99b7 r-lrvibr r-19yznuf r-64el8z r-1dye5f7 r-1loqt21 r-o7ynqc r-6416eg r-1ny4l3l']")).Click();
    Thread.Sleep(2000);

    Console.WriteLine("urlを入力してください");
    string? url = Console.ReadLine();

    Driver.Navigate().GoToUrl(url);

    Thread.Sleep(4000);

    change_learnlist(ref learn_list);

    judgement();

    

    return;
}


void judgement()
{
    att_num=0;
    Console.WriteLine("これで確定ますか？0=やり直し 1=確定");
    string? ans = Console.ReadLine();
    //1==OK;0==no
    if (ans == "1")
    {
        check_change();

        if (keycode == "")
        {
            Console.WriteLine("urlを入力してください");
            string? url = Console.ReadLine();

            Driver.Navigate().GoToUrl(url);
            Thread.Sleep(4000);
            learn_list = new List<string>();
            change_learnlist(ref learn_list);
            judgement();
        }
        else
        {

            //クリップボードにコピー
            int ret=Convert.ToInt16(keycode);
            using (StreamWriter sw = new StreamWriter(@"code.txt", false,
                                                Encoding.GetEncoding("utf-8")))
            {
                sw.WriteLine(ret);
                sw.Close();
            }
        
            Process p = Process.Start(@"move.exe");
            p.WaitForExit();
            return;
        }
    }
    else if (ans == "0")
    {
        Console.WriteLine("urlを入力してください");
        string? url = Console.ReadLine();

        Driver.Navigate().GoToUrl(url);
        Thread.Sleep(4000);
        learn_list = new List<string>();
        change_learnlist(ref learn_list);
        judgement();
    } 
    else
        {
        judgement() ;
    }



}

string check_code(ref List<string> list)
{
    string code="";

    foreach (string line in list)
    {
        code = Regex.Replace(line.Substring(2), "[^0-9]", "");
        if (code!="") break;
    }

    return code;
}





void check_change()
{
    Driver.Navigate().Refresh();
    List<string> check_list = new List<string>();
    Thread.Sleep(2000);
    change_learnlist(ref check_list);
    
    int count = 0;

    foreach (string line in check_list)
    {
        if (line == learn_list[count])
        {
            count++;
        }
        else
        {

            Console.WriteLine(att_num) ;
            Console.WriteLine("更新されました！");

            keycode=check_code(ref check_list);

            return;
        }
    }

    Console.WriteLine("更新されません");
    check_change();
    return ;
}


void change_learnlist(ref List<string> list)
{

    var result = Driver.FindElements(By.XPath(@"//*[@class='css-1qaijid r-bcqeeo r-qvutc0 r-1tl8opc']"));

    int count = 0;

    bool dont_write_flag = false;

    bool first_flag = true;

    bool kotei_flag = false;

    bool constracted = false;

    bool nazonoten = false;

    bool att_flag=false;

    int[] inpres = new int[3];

    int inpres_count = 0;

    int at= att_num;

    int att = at;

    if (att>0)
    {
        att_flag= true;
    }

    foreach (var element in result)
    {
        if (element.Text.Contains("固定"))
        {
            kotei_flag = true;

        }
            if (element.Text.Contains("@"))
            {
            if (att_flag == true)
            {
                att--;
                if (att == 0)
                {
                    att_flag = false;
                }

            }
            else
            {


                if (constracted == true)
                {
                    break;
                }


                if (kotei_flag == true)
                {
                    kotei_flag = false;
                }
                else
                {

                    if (count == 1)
                    {
                        dont_write_flag = false;
                        count = 0;
                    }
                    else
                    {
                        count++;
                        dont_write_flag = true;
                        first_flag = false;
                    }
                }
            }
            }
            else if (first_flag == false && dont_write_flag == false)
            {
                if (int.TryParse(element.Text, out inpres[inpres_count]))
                {
                    inpres_count++;
                    if (inpres_count > 1)
                    {
                        break;
                    }
                }
                else
                {
                    if (nazonoten == false)
                    {
                        nazonoten = true;
                    }
                    else
                    {

                        list.Add(element.Text);
                        Console.WriteLine(element.Text);
                        constracted = true;
                    }
                }
            }

        
    }

}
