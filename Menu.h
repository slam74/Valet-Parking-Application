/*
Created by Simon Lam
Student Number: 150595197
Final Project Milestone 1
Date: 07-10-2020
*/

#ifndef MENU_H_
#define MENU_H_

namespace sdds
{
	const int MAX_NO_OF_ITEMS = 10;

	// Forward declaration class Menu
	class Menu;

	class MenuItem
	{
	private:
		char* desc;

		// private member functions
		MenuItem(const MenuItem&) = delete;		// no copy constructor
		MenuItem& operator=(const MenuItem&) = delete;	// no assignment
		MenuItem();
		MenuItem(const char*);
		~MenuItem();
		friend class Menu;
		void display() const;
	};

	class Menu
	{
	private:
		char* title;	// title of the menu
		MenuItem items[MAX_NO_OF_ITEMS];	// array of MenuItem pointers
		int item_cnt;	// number of MenuItems in the Menu
		int indent;		// level of indentation for display
		void clear();	// sets Menu to invalid empty state

	public:
		Menu();
		Menu(const char*, int = 0);
		~Menu();
		Menu(const Menu&);
		Menu& operator=(const Menu&);
		operator bool() const;
		bool isEmpty() const;
		void display() const;
		void indentDisplay() const;
		Menu& operator=(const char*);
		void add(const char*);
		Menu& operator<<(const char*);
		int run() const;
		operator int() const;
	};
}

#endif
