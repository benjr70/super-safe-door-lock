#include "check.h"

namespace CheckNS
{
	
	Check::Check()
	{
		int oldFirendCount;
		
		file.open("oldFieldCount");
		string s = file.getline();
		stoi()
		// set up connection
		connection.connect(
            "datatest",     // database name
            "Datatest",   // user name
            "THANh123",   // password
            SAConnection::SA_MySQL_client);
       
		command::setConnection(& connection);
		command.setCommandText(); // doc step #2
		readUsers();
		readLog();
       
   
		if (command.fieldCount() != oldFieldcount)
			{
				castJudgement();
			}
	
	}
	
	
	void Check::castJudgement()
	{
		command.setCommandText("SELECT * WHERE access = NULL; ORDER BY access");
		command.Execute();
		std::string searching = command.fetch().asString();
		if (searching != "")
		if (isThereAThreat())
			{
				command.setCommandText("UPDATE access SET TRUE WHERE access = NULL");
			}
		else
			{
				command.setCommandText("UPDATE access SET FALSE WHERE access = NULL");
			}
	}

	bool Check::isThereAThreat() const
	{
		 command.setCommandText("Select * from safedoortable");
		 command.Execute();
			while(command.FetchNext())
			{
				
			}
			// if the same key has been tried multiple times
		std::vector<int>[4] codes;
		command.setCommandText("SELECT *"); 
		// or if all of a sudden multiple fobs have been accessed
		// or if all of a sudden the same user has had problems, block the user
		
		
	}
}
