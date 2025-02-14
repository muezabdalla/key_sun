#define SCREEN_W 1920
#define SCREEN_H 1080-60

i = 1;
while (i < argc)
{
	string arg_current = argv[i];
	if (arg_current == "-h" || arg_current == "--help") {
		print_help();
		i++;
	} else if (arg_current == "-p") {
		// checking if the arguments after -p are less than required
		if (argc-i-1 < 2)
		{
			cout << "too few argument after -p" << endl;
			return 1;
		}

		arg_next = argv[i+1];
		arg_next2 = argv[i+2];

		if (arg_next == "right")
			X = SCREEN_W-BUTTON_WIDTH*nButtons;
		else if (arg_next == "left")
			X = 0;
		else 
			X = atoi(argv[i+1]);

		if (arg_next2 == "top")
			Y = 0;
		else if (arg_next2 == "buttom")
			Y = SCREEN_H-BUTTON_HIEGHT;
		else 
			Y = atoi(argv[i+1]);

		i+=3;
	} else if (arg_current == "-s") {
		// checking if the arguments after -S are less than required
		if (argc-i-1 < 2)
		{
			cout << "too few argument after -S" << endl;
			return 1;
		}

		BUTTON_WIDTH = atoi(argv[i+1]);
		if (BUTTON_WIDTH == 0) // if the input was string this cindition will be true
		{
			cout << argv[i+1] << " is not a valid input" << endl;
			return 1;
		}
		BUTTON_HIEGHT = atoi(argv[i+2]);
		if (BUTTON_HIEGHT == 0) // if the input was string this cindition will be true
		{
			cout << argv[i+2] << " is not a valid input(second)" << endl;
			return 1;
		}

		i+=3;

	} else if (arg_current == "-b") {
		SHOW_BORDERS = false;
		i++;

	} else if (arg_current == "-i") {
		// checking if the arguments after -i are less than required
		if (argc-i-1 < 1)
		{
			cout << "too few argument after -i" << endl;
			return 1;
		}
		arg_next = argv[i+1];
		if (arg_next.size() > 21)
		{
			cout << "this input file path is very long\nare you tring to make a memory issue" << endl;
			return 1;
		}

		strcpy(KEYBOARD_FILE, arg_next.c_str());

		if (!std::filesystem::exists(KEYBOARD_FILE))
		{
			cout << "file " << KEYBOARD_FILE << " does not exist" << endl;
			return 1;
		}
		i+=2;

	} else if (arg_current == "-c") {
		SHOW_CTRL = false;
		i++;
	} else if (arg_current == "-f") {
		SHOW_SHIFT = false;
		i++;
	} else if (arg_current == "-t") {
		SHOW_SUPER = false;
		i++;
	} else if (arg_current == "-a") {
		SHOW_ALT = false;
		i++;

	}
}
