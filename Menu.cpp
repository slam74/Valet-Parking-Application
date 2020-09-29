/*
Created by Simon Lam
Student Number: 150595197
Final Project Milestone 1
Date: 07-10-2020
*/

#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"

namespace sdds
{
	/*=======================================================*/
	/*========== MenuItem Class Member Functions ============*/
	/*=======================================================*/

	// MenuItem default constructor
	MenuItem::MenuItem()
	{
		desc = nullptr;
	}

	// MenuItem custom constructor
	MenuItem::MenuItem(const char* item)
	{
		if (item != nullptr)
		{
			int size = strlen(item);
			desc = new char[size + 1];

			int i;
			for (i = 0;i < size;i++)
			{
				desc[i] = item[i];
			}
			desc[size] = '\0';
		}
		else
		{
			desc = nullptr;
		}
	}

	// MenuItem destructor
	MenuItem::~MenuItem()
	{
		if (desc != nullptr)
		{
			delete[] desc;
			desc = nullptr;
		}
	}

	void MenuItem::display() const
	{
		// if not empty state, display MenuItem contents on the screen
		if (desc != nullptr)
		{
			std::cout << desc << std::endl;
		}
		else
		{
			std::cout << std::endl;
		}
	}

	/*=======================================================*/
	/*============= Menu Class Member Functions =============*/
	/*=======================================================*/

	// Menu default constructor
	Menu::Menu()
	{
		title = nullptr;

		int i;

		for (i = 0;i < item_cnt;i++)
		{
			if (items[i].desc != nullptr)
			{
				delete[] items[i].desc;
				items[i].desc = nullptr;
			}
		}
		item_cnt = 0;
		indent = 0;
	}

	// Menu custom constructor
	Menu::Menu(const char* str, int ind)
	{
		if (str != nullptr && str[0] != '\0')
		{
			int size = strlen(str);
			title = new char[size + 1];

			int i;
			for (i = 0;i < size;i++)
			{
				title[i] = str[i];
			}
			title[size] = '\0';
			item_cnt = 0;
			indent = ind;
			for (i = 0;i < MAX_NO_OF_ITEMS;i++)
			{
				items[i].desc = nullptr;
			}
		}
		else
		{
			clear();
		}
	}

	Menu::~Menu()
	{
		if (title != nullptr)
		{
			delete[] title;
			title = nullptr;
		}

		if (item_cnt != 0)
		{
			int i;
			for (i = 0;i < item_cnt;i++)
			{
				if (items[i].desc != nullptr)
				{
					delete[] items[i].desc;
					items[i].desc = nullptr;
				}
			}
		}
	}

	// Menu copy constructor
	Menu::Menu(const Menu& src)
	{
		// shallow copy non-resource variables
		int i, j;
		for (i = 0;i < src.item_cnt;i++)
		{
			int size = strlen(src.items[i].desc);
			items[i].desc = new char[size + 1];

			for (j = 0;j < size;j++)
			{
				items[i].desc[j] = src.items[i].desc[j];
			}
			items[i].desc[size] = '\0';
		}

		item_cnt = src.item_cnt;
		indent = src.indent;

		// allocate dynamic memory
		if (src.title != nullptr)
		{
			int i, size = strlen(src.title);
			title = new char[size + 1];

			for (i = 0;i < size;i++)
			{
				title[i] = src.title[i];
			}
			title[size] = '\0';
		}
		else
		{
			title = nullptr;
		}
	}

	// Menu copy and assignment
	Menu& Menu::operator=(const Menu& src)
	{
		// check for self assignment
		if (this != &src)
		{
			// shallow copy non-resource variables
			item_cnt = src.item_cnt;
			indent = src.indent;

			int i, j;
			for (i = 0;i < src.item_cnt;i++)
			{
				// deallocate old descriptions if needed
				if (items[i].desc != nullptr)
				{
					delete[] items[i].desc;
				}
				
				// allocate new dynamic memory
				int size = strlen(src.items[i].desc);
				items[i].desc = new char[size + 1];

				for (j = 0;j < size;j++)
				{
					items[i].desc[j] = src.items[i].desc[j];
				}
				items[i].desc[size] = '\0';
			}

			// deallocate old title
			delete[] title;

			if (src.title != nullptr)
			{
				// allocate new dynamic memory
				int i, size = strlen(src.title);
				title = new char[size + 1];

				for (i = 0;i < size;i++)
				{
					title[i] = src.title[i];
				}
				title[size] = '\0';
			}
			else
			{
				title = nullptr;
			}
		}
		return *this;
	}

	// Menu bool cast overload: returns true if Menu is valid, otherwise false
	Menu::operator bool() const
	{
		return !isEmpty();
	}

	// returns true if the Menu is in an empty state, otherwise false
	bool Menu::isEmpty() const
	{
		if (title == nullptr && item_cnt == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Menu::display() const
	{
		if (isEmpty())
		{
			std::cout << "Invalid Menu!" << std::endl;
		}
		else if (item_cnt == 0)
		{
			indentDisplay();
			std::cout << title << std::endl;
			std::cout << "No Items to display!" << std::endl;
		}
		else
		{
			indentDisplay();
			std::cout << title << std::endl;
			int row, i;
			for (i = 0, row = 1;i < item_cnt;i++, row++)
			{
				indentDisplay();
				std::cout << row << "- ";
				items[i].display();
			}
			indentDisplay();
			std::cout << "> ";
		}
	}

	// indent menu display based on indentation level
	void Menu::indentDisplay() const
	{
		int i;
		for (i = 0;i < indent;i++)
		{
			std::cout << "    ";
		}
	}

	// Menu copy assignment operator: a Menu can be 
	// assigned to a char C-string to reset the title 
	// of the Menu to the newly assigned string
	Menu& Menu::operator=(const char* str)
	{
		if (str != nullptr)
		{
			// deallocate old title
			delete[] title;

			// allocate new memory
			int i, size = strlen(str);
			title = new char[size + 1];

			for (i = 0;i < size;i++)
			{
				title[i] = str[i];
			}
			title[size] = '\0';
		}
		else
		{
			clear();
		}
		return *this;
	}

	// creates a dynamic MenuItem out of the C-string argument 
	// and add it to the array of MenuItem pointers
	void Menu::add(const char* str)
	{
		// check if Menu is not empty and number of items is less than max capacity
		if (!isEmpty() && item_cnt < MAX_NO_OF_ITEMS)
		{
			// check for valid parameter string
			if (str != nullptr)
			{
				// increase number of MenuItems
				item_cnt += 1;

				// dynamically allocate desc in MenuItems array
				int size = strlen(str);
				items[item_cnt - 1].desc = new char[size + 1];

				int i;
				for (i = 0;i < size;i++)
				{
					items[item_cnt - 1].desc[i] = str[i];
				}
				items[item_cnt - 1].desc[size] = '\0';
			}
			else
			{
				clear();
			}
		}
	}

	// works exactly like add()
	Menu& Menu::operator<<(const char* str)
	{
		add(str);
		return *this;
	}

	// displays the Menu and waits for the user's 
	// response to select an option by entering the row number
	// of the MenuItems
	int Menu::run() const
	{
		int selection = 0;
		display();
		if (!isEmpty() && item_cnt > 0)
		{
			Utils::read(selection, 1, item_cnt, "Invalid selection, try again: ");
		}
		return selection;
	}

	// sets Menu to invalid empty state
	void Menu::clear()
	{
		if (title != nullptr) {
			delete[] title;
			title = nullptr;
		}

		int i;
		
		for (i = 0;i < item_cnt;i++)
		{
			if (items[i].desc != nullptr)
			{
				delete[] items[i].desc;
				items[i].desc = nullptr;
			}
		}
		item_cnt = 0;
		indent = 0;
	}

	// integer cast overload: if the Menu object is
	// casted to an integer, run() is called
	Menu::operator int() const
	{
		return run();
	}

}