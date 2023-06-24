#include<iostream>
#include<fstream>
using namespace std;
class Date;
class Posts;
class Memory;
class Comments;
class Object;
class Pages;
class Users;
class Activity;
class SocialNetwork;
class Helper {
public:
	static int StringLenght(char* str) {
		int count = 0;
		for (int i = 0; str[i] != '\0'; i++)
			count++;
		return count;

	}
	static void StringCopy(char*& dest, char*& src) {
		int i;
		for (i = 0; src[i] != '\0'; i++)
			dest[i] = src[i];
		dest[i] = '\0';
	}
	static char* GetStringFromBuffer(char* str) {
		int l = StringLenght(str);
		char* newstr = new char[l + 1];
		StringCopy(newstr, str);
		return newstr;
	}
	static int StringLenght(const char* str) {
		int count = 0;
		for (int i = 0; str[i] != '\0'; i++)
			count++;
		return count;

	}
	static void StringCopy(char*& dest, const char*& src) {
		int i;
		for (i = 0; src[i] != '\0'; i++)
			dest[i] = src[i];
		dest[i] = '\0';
	}
	static char* GetStringFromBuffer(const char* str) {
		int l = StringLenght(str);
		char* newstr = new char[l + 1];
		StringCopy(newstr, str);
		return newstr;
	}
	static bool FindExactMatch(char* string, char* tofind) {
		int l = StringLenght(tofind);
		bool check = false;
		int i;
		for (i = 0; i < l; i++) {
			if (string[i] == tofind[i] || string[i] == tofind[i] + 32 || string[i] + 32 == tofind[i])
				check = true;
			else {
				check = false;
				break;
			}
		}
		return check;
	}
	static bool FindExactMatch(const char* string, const char* tofind) {
		int l = StringLenght(tofind);
		bool check = false;
		int i;
		for (i = 0; i < l; i++) {
			if (string[i] == tofind[i] || string[i] == tofind[i] + 32 || string[i] + 32 == tofind[i])
				check = true;
			else {
				check = false;
				break;
			}
		}
		return check;
	}
	static char* GenerateNewID(const char* prefix, int postfix)
	{
		char buffer[20];
		int i, l = StringLenght(prefix);
		for (i = 0; i < l; i++)
			buffer[i] = prefix[i];
		int n = postfix;
		while (n > 10)
		{
			n = postfix % 10;
			postfix = postfix / 10;
			buffer[i] = postfix + '0';
			i++;
		}
		buffer[i++] = n + '0';
		buffer[i] = '\0';
		char* newID = GetStringFromBuffer(buffer);
		return newID;
	}
};
class Date
{
	int day;
	int month;
	int year;
public:
	static Date currentDate;
	Date()
	{
		day = month = year = 0;
	}
	int FindDifference()
	{
		return currentDate.year - year;
	}
	bool CompareDayAndMonth()
	{
		return (day == currentDate.day && month == currentDate.month);
	}
	static void SetCurrentDate(int D, int M, int Y)
	{
		currentDate.day = D;
		currentDate.month = M;
		currentDate.year = Y;
	}
	bool operator==(Date date)
	{
		if ((day == date.day || day == (date.day - 1)) && month == date.month && year == date.year)
			return true;
		else if (date.month == month - 1 && day - 1 == 0)
			return true;
		else
			return false;
	}
	void ReadDateFromFile(ifstream& read)
	{
		read >> day;
		read >> month;
		read >> year;
	}
	void ViewDate()
	{
		cout << " (" << day << "/" << month << "/" << year << ")";
	}
	~Date()
	{

	}
};
class Object
{
	char* ID;
public:
	Object()
	{
		ID = 0;
	}
	void SetID(char* temp)
	{
		ID = Helper::GetStringFromBuffer(temp);
	}
	char* GetID()
	{
		return ID;
	}
	virtual void PrintListView() = 0;
	virtual void AddToTimeLine(Posts* shared) = 0;
	virtual void DisplayCurrent() = 0;
	virtual ~Object()
	{
		if (ID)
			delete[]ID;
	}
};
class Activity
{
	char* description;
	int type;
public:
	Activity()
	{
		description = 0;
		type = 0;
	}
	void ReadActivityDataFromFile(ifstream& read)
	{
		char buffer[40];
		read >> type;
		read.getline(buffer, 40);
		description = Helper::GetStringFromBuffer(buffer);
	}
	void PrintActivity()
	{
		switch (type)
		{
		case 1:cout << " is feeling ";
			break;
		case 2:cout << " is thinking about ";
			break;
		case 3:cout << " is makung ";
			break;
		case 4:cout << " is celebrating ";
			break;
		}
		cout << description;
	}
	~Activity()
	{
		if (description)
			delete[]description;
	}
};
class Comments
{
	char* ID;
	char* text;
	Object* sharedBy;
public:
	static int commentCount;
	Comments()
	{
		text = ID = 0;
		sharedBy = 0;
	}
	Comments(const char* txt, Object* share)
	{
		ID = Helper::GenerateNewID("c", ++commentCount);
		text = Helper::GetStringFromBuffer(txt);
		sharedBy = share;
	}
	void SetValues(char* id, char* txt, Object* obj)
	{
		ID = Helper::GetStringFromBuffer(id);
		text = Helper::GetStringFromBuffer(txt);
		sharedBy = obj;
	}
	void PrintComment()
	{
		cout << "\n\t";
		sharedBy->DisplayCurrent();
		cout << " wrote:\t\"" << text << "\".";
	}
	~Comments()
	{
		if (ID)
			delete[]ID;
		if (text)
			delete[]text;
	}
};
class Posts
{
	char* ID;
	char* description;
	int type;
	Activity* activity;
	Date sharedDate;
	Object* sharedBy;
	Object** likedBy;
	Comments** comments;
	int commentsCount;
	int likedByCount;
public:
	static int postCount;
	Posts()
	{
		ID = description = 0;
		activity = 0;
		likedBy = 0;
		sharedBy = 0;
		comments = 0;
		type = likedByCount = commentsCount = 0;
	}
	char* GetID()
	{
		return ID;
	}
	Date GetDate()
	{
		return sharedDate;
	}
	void ReadPostDataFromFile(ifstream& read)
	{
		read >> type;
		char buffer[100];
		read >> buffer;
		ID = Helper::GetStringFromBuffer(buffer);
		sharedDate.ReadDateFromFile(read);
		read.getline(buffer, 100);
		read.getline(buffer, 100);
		description = Helper::GetStringFromBuffer(buffer);
		if (type == 2)
		{
			activity = new Activity;
			activity->ReadActivityDataFromFile(read);
		}
	}
	void AssignSharedBy(Object* obj)
	{
		sharedBy = obj;
	}
	void AddToLikedBy(Object* obj)
	{
		if (likedByCount < 10)
		{
			if (likedBy == 0 && obj)
				likedBy = new Object * [10];
			if (obj)
				likedBy[likedByCount++] = obj;
		}
	}
	void AddComment(Comments* temp)
	{
		if (temp && comments == 0)
			comments = new Comments * [10];
		if (temp && commentsCount < 10)
			comments[commentsCount++] = temp;
	}
	virtual void PrintPost(bool dateCheck = true, bool commentCheck = true)
	{
		cout << "\n\n---";
		sharedBy->DisplayCurrent();
		if (activity)
		{
			activity->PrintActivity();
			cout << "\n";
		}
		else
			cout << " shared";
		cout << " \"" << description << "\"";
		if(dateCheck)
			sharedDate.ViewDate();
		if (commentCheck)
			for (int i = 0; i < commentsCount; i++)
				comments[i]->PrintComment();
	}
	void ViewLikedByList()
	{
		if (likedBy)
		{
			cout << "\nCommand:\t\t\t\tView Liked By List: (" << ID << ")\nPost Liked By : \n";
			for (int i = 0; i < likedByCount; i++)
				likedBy[i]->PrintListView();
		}
		else
			cout << "\n No one liked this Post.";
	}
	char* GetText() 
	{
		return description;
	}
	Object* GetSharedBy()
	{
		return sharedBy;
	}
	void SetValues(Posts* temp, const char* text)
	{
		ID = Helper::GenerateNewID("post", ++postCount);
		sharedBy = temp->sharedBy;
		sharedDate = Date::currentDate;
		description = Helper::GetStringFromBuffer(text);
	}
	~Posts()
	{
		if (ID)
			delete[]ID;
		if (description)
			delete[]description;
		if (activity)
			delete activity;
		if (likedBy)
			delete[]likedBy;
		if (comments)
		{
			for (int i = 0; i < commentsCount; i++)
				delete comments[i];
			delete[]comments;
		}
	}
};
class Memory :public Posts
{
	Posts* originalPost;
public:
	Memory()
	{
		originalPost = 0;
	}
	Memory(Posts* temp, const char* txt)
	{
		originalPost = temp;
		SetValues(temp, txt);
	}
	void PrintPost(bool dateCheck = true, bool commentCheck = true)
	{
		cout << "\n\n---";
		GetSharedBy()->DisplayCurrent();
		cout << " shared a Memory~~~";
		GetDate().ViewDate();
		cout << "\n \"" << GetText() << ".\"\n\t\t(" << originalPost->GetDate().FindDifference() << " Years Ago)";
		originalPost->PrintPost(true, false);
	}
};
class Pages : public Object
{
	char* Tittle;
	Posts** timeLine;
	int timeLineCount;
public:
	Pages()
	{
		Tittle = 0;
		timeLine = 0;
		timeLineCount = 0;
	}
	void ReadPagesDataFromFile(ifstream& read)
	{
		char temp[100];
		read >> temp;
		SetID(temp);
		read.getline(temp, 100);
		Tittle = Helper::GetStringFromBuffer(temp);
	}
	void DisplayCurrent()
	{
		cout << Tittle;
	}
	void PrintListView()
	{
		cout << "\n" << GetID() << "\t-\t" << Tittle;
	}
	void AddToTimeLine(Posts* shared)
	{
		if (shared && timeLine == 0)
			timeLine = new Posts * [10];
		if (shared && timeLineCount < 10)
			timeLine[timeLineCount++] = shared;
	}
	void ViewPage()
	{
		cout << "\n\nCommand:\t\t\t\tView Page(" << GetID() << "):\n" << Tittle << " - Timeline";
		if (timeLine)
			for (int i = 0; i < timeLineCount; i++)
				timeLine[i]->PrintPost();
	}
	void PrintLatestPost()
	{
		for (int i = 0; i < timeLineCount; i++)
			if (timeLine[i]->GetDate() == Date::currentDate)
				timeLine[i]->PrintPost(false);
	}
	~Pages()
	{
		if (Tittle)
			delete[]Tittle;
		if (timeLine)
		{
			for (int i = 0; i < timeLineCount; i++)
				if (timeLine[i])
					delete timeLine[i];
			delete[]timeLine;
		}
	}
};
class Users : public Object
{
	char* firstName;
	char* lastName;
	Users** friendsList;
	Pages** likedPagesList;
	Posts** timeLine;
	int timeLineCount;
	int likedPagesCount;
	int friendsCount;
public:
	Users()
	{
		firstName = lastName = 0;
		likedPagesCount = friendsCount = timeLineCount = 0;
		friendsList = 0;
		likedPagesList = 0;
		timeLine = 0;
	}
	void ReadUsersDataFromFile(ifstream& fin)
	{
		char temp[30];
		fin >> temp;
		SetID(temp);
		fin >> temp;
		firstName = Helper::GetStringFromBuffer(temp);
		fin >> temp;
		lastName = Helper::GetStringFromBuffer(temp);
	}
	void AddToLikedPagesList(Pages* liked)
	{
		if (liked != 0 && likedPagesCount == 0)
			likedPagesList = new Pages * [10];
		if (likedPagesCount < 10 && liked != 0)
			likedPagesList[likedPagesCount++] = liked;
	}
	void AddToFriendsList(Users* frienduser)
	{
		if (frienduser != 0 && friendsCount == 0)
			friendsList = new Users * [10];
		if (friendsCount < 10 && frienduser != 0)
			friendsList[friendsCount++] = frienduser;
	}
	void PrintListView()
	{
		cout << "\n" << GetID() << "\t-\t" << firstName << " " << lastName;
	}
	void DisplayCurrent()
	{
		cout << firstName << " " << lastName;
	}
	void DisplayCurrentUser()
	{
		cout << firstName << " " << lastName << " Successfully Set As Current User.";
	}
	void DisplayLikedPagesList()
	{
		cout << "\n\nCommand:\t\t\t\tView Liked Pages.\n";
		cout << firstName << " " << lastName << " - Liked Pages:\n";
		if (likedPagesCount != 0)
			for (int i = 0; i < likedPagesCount; i++)
				likedPagesList[i]->PrintListView();
		else
			cout << "\n\n No Pages found in Liked Pages List.";
	}
	void DisplayFriendsList()
	{
		cout << "\n\nCommand:\t\t\t\tView Friend List.\n";
		cout << firstName << " " << lastName << " - Friend List:\n";
		if (friendsCount != 0)
			for (int i = 0; i < friendsCount; i++)
				friendsList[i]->PrintListView();
		else
			cout << "\n\n No Friends found in Friends List.";
	}
	void AddToTimeLine(Posts* shared)
	{
		if (shared && timeLine == 0)
			timeLine = new Posts * [10];
		if (shared && timeLineCount < 10)
			timeLine[timeLineCount++] = shared;
	}
	void PrintLatestPost()
	{
		for (int i = 0; i < timeLineCount; i++)
			if (timeLine[i]->GetDate() == Date::currentDate)
				timeLine[i]->PrintPost(false);
	}
	void ViewHome()
	{
		cout << "\n\n Command:\t\t\t\tView Home\n" << firstName << " " << lastName << " - Home Page:\n";
		if (friendsList)
			for (int i = 0; i < friendsCount; i++)
						friendsList[i]->PrintLatestPost();
		if (likedPagesList)
			for (int i = 0; i < likedPagesCount; i++)
				likedPagesList[i]->PrintLatestPost();
	}
	void ViewTimeLine()
	{
		cout << "\n\nCommand:\t\t\t\tView Time Line:\n" << firstName << " " << lastName << " - Time Line";
		for (int i = 0; i < timeLineCount; i++)
			timeLine[i]->PrintPost();
	}
	void PostComment(Posts* reqPost, const char* comment)
	{
		cout << "\nCommand:\t\t\t\tPost Comment(" << reqPost->GetID() << ", \"" << comment << "\")";
		Comments* newComment = new Comments(comment, this);
		reqPost->AddComment(newComment);
	}
	void SeeYourMemories()
	{
		cout << "\nCommand:\t\t\t\tSeeYourMemories()\n\n  We hope you emjoy looking back and sharing your Memories on Facebook, from the most recent to those long ago.\n";
		int n = 0;
		for (int i = 0; i < timeLineCount; i++)
		{
			n = timeLine[i]->GetDate().FindDifference();
			if (n && timeLine[i]->GetDate().CompareDayAndMonth())
			{
				cout << "\nOn This Day\n" << n << " Years Ago:";
				timeLine[i]->PrintPost();
			}
		}
	}
	~Users()
	{
		if (firstName)
			delete[]firstName;
		if (lastName)
			delete[]lastName;
		if (friendsList)
			delete[]friendsList;
		if (likedPagesList)
			delete[]likedPagesList;
		if (timeLine) 
		{
			for (int i = 0; i < timeLineCount; i++)
				if(timeLine[i])
					delete timeLine[i];
			delete[]timeLine;
		}
	}
};
class SocialNetwork
{
	Pages** pagesList;
	Users** usersList;
	Posts** postsList;
	int userCount;
	int pageCount;
public:
	SocialNetwork()
	{
		pagesList = 0;
		usersList = 0;
		postsList = 0;
		pageCount = userCount = 0;
	}
	//There are 2 of the Search functions for Users and Pages, this is just to deal with the const and non-const parameters. if we took inputs in the Execute functions, this would not have been required.
	Pages* SearchPageByID(char* id)
	{
		if (id)
			for (int i = 0; i < pageCount; i++)
			{
				bool check = Helper::FindExactMatch(pagesList[i]->GetID(), id);
				if (check)
					return pagesList[i];
			}
		return 0;
	}
	Pages* SearchPageByID(const char* id)
	{
		if (id)
			for (int i = 0; i < pageCount; i++)
			{
				bool check = Helper::FindExactMatch(pagesList[i]->GetID(), id);
				if (check)
					return pagesList[i];
			}
		return 0;
	}
	Users* SearchUserByID(char* id)
	{
		if (id)
			for (int i = 0; i < userCount; i++)
			{
				bool check = Helper::FindExactMatch(usersList[i]->GetID(), id);
				if (check)
					return usersList[i];
			}
		return 0;
	}
	Users* SearchUserByID(const char* id)
	{
		if (id)
			for (int i = 0; i < userCount; i++)
			{
				bool check = Helper::FindExactMatch(usersList[i]->GetID(), id);
				if (check)
					return usersList[i];
			}
		return 0;
	}
	Posts* SearchPostByID(const char* id)
	{
		if (id)
			for (int i = 0; i < Posts::postCount; i++)
			{
				bool check = Helper::FindExactMatch(postsList[i]->GetID(), id);
				if (check)
					return postsList[i];
			}
		return 0;
	}
	Object* SearchObjectById(char* id)
	{
		if (id[0] == 'u')
			return SearchUserByID(id);
		else
			return SearchPageByID(id);
	}
	void ExpandPosts(Posts* m)
	{
		Posts::postCount++;
		Posts** newer = new Posts * [Posts::postCount];
		for (int i = 0; i < Posts::postCount - 1; i++)
			newer[i] = postsList[i];
		newer[Posts::postCount - 1] = m;
		delete[]postsList;
		postsList = newer;
	}
	void ShareMemory(Posts* newMemory, const char* txt)
	{
		Memory* newPost = new Memory(newMemory, txt);
		ExpandPosts(newPost);
	}
	void LoadPagesFromFile(const char* fileName)
	{
		ifstream read(fileName);
		if (read.is_open())
		{
			read >> pageCount;
			if (pageCount)
				pagesList = new Pages * [pageCount];
			for (int i = 0; i < pageCount; i++)
			{
				pagesList[i] = new Pages();
				pagesList[i]->ReadPagesDataFromFile(read);
			}
			read.close();
		}
		else
			cout << "\nFailed to Open File " << fileName;
	}
	void LoadUsersFromFile(const char* fileName)
	{
		ifstream read(fileName);
		char*** tempUserIds = new char** [userCount];
		if (read.is_open())
		{
			read >> userCount;
			usersList = new Users * [userCount];
			char*** tempUserIds = new char** [userCount];
			for (int i = 0; i < userCount; i++)
			{
				usersList[i] = new Users();
				usersList[i]->ReadUsersDataFromFile(read);
				tempUserIds[i] = new char* [10];
				char buffer[100];
				buffer[0] = ' ';
				int j = 0;
				while (buffer[0] != '-')
				{
					read >> buffer;
					tempUserIds[i][j] = Helper::GetStringFromBuffer(buffer);
					j++;
				}
				tempUserIds[i][j] = 0;
				buffer[0] = ' ';
				while (buffer[0] != '-')
				{
					read >> buffer;
					Pages* liked = SearchPageByID(buffer);
					usersList[i]->AddToLikedPagesList(liked);
				}
			}
			read.close();
			for (int i = 0; i < userCount; i++)
			{
				int j = 0;
				while (tempUserIds[i][j] != 0) {
					Users* befriend = SearchUserByID(tempUserIds[i][j]);
					usersList[i]->AddToFriendsList(befriend);
					delete[]tempUserIds[i][j];
					j++;
				}
				delete[]tempUserIds[i];
			}
			delete[]tempUserIds;
		}
		else
			cout << "\nFailed to Open File " << fileName;
	}
	void LoadPostsFromFile(const char* fileName)
	{
		ifstream read;
		read.open(fileName);
		if (read.is_open())
		{
			read >> Posts::postCount;
			if (Posts::postCount)
				postsList = new Posts * [Posts::postCount];
			int i = 0;
			while (i < Posts::postCount)
			{
				postsList[i] = new Posts;
				postsList[i]->ReadPostDataFromFile(read);
				char buffer[30];
				buffer[0] = ' ';
				read >> buffer;
				Object* obj = SearchObjectById(buffer);
				postsList[i]->AssignSharedBy(obj);
				obj->AddToTimeLine(postsList[i]);
				while (buffer[0] != '-')
				{
					read >> buffer;
					obj = SearchObjectById(buffer);
					postsList[i]->AddToLikedBy(obj);
				}
				i++;
			}
			read.close();
		}
		else
			cout << "\nFailed to Open File " << fileName;
	}
	void LoadCommentsFromFile(const char* fileName)
	{
		ifstream read;
		read.open(fileName);
		char id[10], text[100], buffer[30];
		if (read.is_open())
		{
			read >> Comments::commentCount;
			for (int i = 0; i < Comments::commentCount; i++)
			{
				Comments* newComment = new Comments;
				read >> id;
				read >> buffer;
				Posts* searchedPost = SearchPostByID(buffer);
				read >> buffer;
				Object* searchedSharedBy = SearchObjectById(buffer);
				read.getline(text, 100);
				newComment->SetValues(id, text, searchedSharedBy);
				searchedPost->AddComment(newComment);
			}
			read.close();
		}
		else
			cout << "\nFailed to Open File " << fileName;
	}
	void LoadSocialNetwork() {
		LoadPagesFromFile("SocialNetworkPages.txt");
		LoadUsersFromFile("SocialNetworkUsers.txt");
		LoadPostsFromFile("SocialNetworkPosts.txt");
		LoadCommentsFromFile("SocialNetworkComments.txt");
	}
	void ExecuteSocialNetwork()
	{
		const char* id = "u7";
		cout << "------------------------------------------------------------------------------------------------------------------------";
		cout << "\nCommand:\t\t\t\tSet Current User " << id;
		Users* reqUser = SearchUserByID(id);
		Date::SetCurrentDate(15, 11, 2017);
		if (reqUser)
		{
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->DisplayCurrentUser();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->DisplayFriendsList();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->DisplayLikedPagesList();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->ViewHome();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->ViewTimeLine();
			const char* postId = "post5";
			Posts* reqPost = SearchPostByID(postId);
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqPost->ViewLikedByList();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			cout << "\n\nCommand:\t\t\t\tLike Post(" << reqPost->GetID() << ")\n\n";
			reqPost->AddToLikedBy(reqUser);
			reqPost->ViewLikedByList();
			postId = "post4";
			reqPost = SearchPostByID(postId);
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->PostComment(reqPost, "Good Luck for your Result");
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			cout << "\n\nCommand:\t\t\t\tView Post(" << reqPost->GetID() << ")";
			reqPost->PrintPost();
			postId = "post8";
			reqPost = SearchPostByID(postId);
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->PostComment(reqPost, "Thanks for all the wishes.");
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			cout << "\n\nCommand:\t\t\t\tView Post(" << reqPost->GetID() << ")";
			reqPost->PrintPost();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			postId = "post10";
			reqPost = SearchPostByID(postId);
			reqUser->SeeYourMemories();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			ShareMemory(reqPost, "Never thought I will be Specialized in this field.");
			reqUser->AddToTimeLine(postsList[Posts::postCount - 1]);
			reqUser->ViewTimeLine();
			const char* pageId = "p1";
			Pages* reqPage = SearchPageByID(pageId);
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqPage->ViewPage();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
		}
		else
			cout << "\n User with ID " << id << " does not exist.";
		id = "u11";
		cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
		cout << "\n Command:\t\t\t\tSet Current User " << id << endl;
		reqUser = SearchUserByID(id);
		if (reqUser)
		{
			reqUser->DisplayCurrentUser();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->ViewHome();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->ViewTimeLine();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
		}
	}
	~SocialNetwork()
	{
		if (pagesList)
		{
			for (int i = 0; i < pageCount; i++)
				if (pagesList[i])
					delete pagesList[i];
			delete[]pagesList;
		}
		if (usersList)
		{
			for (int i = 0; i < userCount; i++)
				if (usersList[i])
					delete usersList[i];
			delete[]usersList;
		}
		if (postsList)
			delete[]postsList;
	}
};
//Initializing all static variables used/declared in various classes.
int Comments::commentCount = 0;
int Posts::postCount = 0;
Date Date::currentDate = Date();
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SocialNetwork FaceBook;
	FaceBook.LoadSocialNetwork();
	FaceBook.ExecuteSocialNetwork();
	return 0;
}