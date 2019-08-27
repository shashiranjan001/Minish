#include<bits/stdc++.h>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <sys/param.h>
#include <unistd.h>
#include <fcntl.h>
#include<sys/wait.h>
#include <time.h>

using namespace std;

int main()
{
	cout<<"\n\tPlease select one of the options\n\n";
	cout<<"\tA. Run an internal command\n\n";
	cout<<"\tB. Run an external command\n\n";
	cout<<"\tC. Run an external command by redirecting standard input from a file\n\n";
	cout<<"\tD. Run an external command by redirecting standard ouput to a file\n\n";
	cout<<"\tE. Run an external command in the background\n\n";
	cout<<"\tF. Run an several external commands in the pipe mode\n\n";
	cout<<"\tG. Quit the shell\n\n";

	char n;
	cout<<"\t Enter your Choice : ";
	cin >>n;
	while(n != 'A' && n != 'B' && n != 'C' && n != 'D' && n != 'E' && n != 'F' && n != 'G')
		{
			cout<<"\tPlease enter a valid option\n";
			cout<<"\n\tEnter your new Choice : ";
			cin >>n;
		}
	cout<<"\n Selected Option is : "<<n<<"\n\n";



	while(n!= 'G')
	{
	    string cmd,temp;
		cin.ignore();
		cout<< "Your Command Here : ";
		getline(cin, cmd);
		//cout<<"\n"<<"hit\t"<<s<<"\n";
		vector<string> cmds;
		int x=0;
		while(x < cmd.length())
		{
			if(cmd[x] == ' ')
			{
				cmds.push_back(temp);
				temp.clear();
				x++;
			}

			else temp+=cmd[x++];
		}
		cmds.push_back(temp);


		pid_t p = fork();

		if (p < 0)
	    {
	        fprintf(stderr, "fork Failed" );
	        return 1;
	    }

	    else if(p == 0)
	    {


			if(n == 'A')
			{
				if(cmds[0] == "mkdir")
				{
					string s;
					s+= cmds[0];
					s+=" -p ";
					s+= cmds[1];
					const int dir_err = system(s.c_str());
				}

				if(cmds[0] == "chdir")
				{
					string s;
					s+= cmds[1];
					chdir(s.c_str());
				}

				if(cmds[0] == "rmdir")
				{
					string s;
					s+= cmds[1];
					rmdir(s.c_str());
				}

			//const int dir_err = system("mkdir -p ./xssyz");
			}

			if(n == 'B')
			{
				int sz =cmds.size();
				 char *argv[sz+1];
				 x =0;
				 while(x!=sz)
				 {
				 	argv[x] = strdup(cmds[x].c_str());
				 	x++;
				 }

				argv[x] = NULL;
				execvp((cmds[0].c_str()), argv);
				cout<<endl;
			}

			if(n == 'C')
			{
				int i = open(cmds[2].c_str(), O_RDONLY);
				fclose(stdin);
				dup(i);
				execlp(cmds[0].c_str(),NULL);
			}

			if(n == 'D')
			{
				int sz =cmds.size();
				int i = open(cmds[sz-1].c_str(), O_CREAT|O_RDWR, 0666);
				fclose(stdout);
				dup(i);
				char *argv[sz-1];
				 x =0;
				 while(x!=sz-2)
				 {
				 	argv[x] = strdup(cmds[x].c_str());
				 	x++;
				 }
				argv[x] = NULL;
				execvp((cmds[0].c_str()), argv);
				cout<<endl;
			}

			if(n == 'E')
			{
				int sz =cmds.size();
				 char *argv[sz];
				 x =0;
				 while(x!=sz-1)
				 {
				 	argv[x] = strdup(cmds[x].c_str());
				 	x++;
				 }

				argv[x] = NULL;
				execvp((cmds[0].c_str()), argv);
				cout<<endl;
			}

			if(n == 'F')
			{
				int num_pipes = 0;
				int num_commands;
				vector<vector<string> > commands;

				vector<string> temp;
				commands.clear();
				temp.clear();
				for(int k = 0;k<=cmds.size();k++)
				{
					if(cmds[k].compare("|") != 0 && k < cmds.size())
					{
						temp.push_back(cmds[k]);
					}

					else
					{
						num_pipes++;
						commands.push_back(temp);
						temp.clear();
					}
				}

				num_commands = commands.size();
				pid_t pid;
				int pipe_array[num_pipes][2];
				int m =0;
				while(m < num_pipes)
				{
					if (pipe(pipe_array[m])==-1)
			    {
			        fprintf(stderr, "Pipe Failed" );
			        return 1;
			    }
					m++;
				}
				int i = 0; // i (iterator for number of commands executed)
				while(i < num_commands)
				{
						pid = fork();
						if(pid < 0)
						{
							fprintf(stderr, "fork Failed" );
			        return 1;
						}
						else if(pid == 0)
						{
							if(i!=0)
							{
								fclose(stdin);
								dup(pipe_array[i-1][0]);
							}
							if(i!= num_commands-1)
							{
								fclose(stdout);
								dup(pipe_array[i][1]);
							}

							int sz=commands[i].size();
							char *argv[sz+1];
							int x =0;
							 while(x!=sz)
							 {
							 	argv[x] = strdup(commands[i][x].c_str());
							 	x++;
							 }

							argv[x] = NULL;
							execvp((commands[i][0].c_str()), argv);
							cout<<endl;
							exit(0);
						}

						else if(pid > 0)
						{
							wait(NULL);
							i++;
						}
				}
				//cout << "\nouter cout here !!! mind you !! i : "<<i<<endl;
				exit(0);
			}
		}

		else {
						if(n != 'E') wait(NULL);
						cout<<"\n\tEnter your next Choice : ";
						cin >> n;
						cout<<"\n";
				}

		}
	}
