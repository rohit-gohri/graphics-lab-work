
    while (c != 4)
    {   std::cout << "Menu\n\n1. Define Object\n2. Transform Object\n3. View Object\n4. Exit\n";
        std::cin >> c;

        switch(c)
        {
        case 1:
            std::cout << "Enter number of points in object\n";
            std::cin >> n;
            obj.resize(n);
            std::cout << "Enter points\n";
            for(int i = 0; i < n; i++)
            {
                obj[i].resize(3);
                std::cin >> obj[i][0];
                std::cin >> obj[i][1];
                obj[i][2] = 1;
            }
            break;
        case 2:
            std::cout << "\nTranformations: \n1. Translate\n2. Scale\n3. Rotate\n4. Back\n";
            std::cin >> t;
            switch(t)
            {
            case 1:
                int tx, ty;
                while (!ismouseclick(WM_LBUTTONDOWN)) {}
                getmouseclick(WM_LBUTTONDOWN, tx, ty);
                for(int i = 0; i < n; i++) {
                    trans(obj[i], tx, ty);
                }
                break;
            case 2:
                float sx, sy;
                std::cout << "\nEnter scaling factor\n";
                std::cin >> sx >> sy;
                for(int i = 0; i < n; i++){
                    scale(obj[i], sx, sy);
                }
                break;
            case 3:
                int ang;
                std::cout << "\nEnter Angle\n";
                std::cin >> ang;
                for(int i = 0; i < n; i++){
                    rot(obj[i], -ang);
                }
                break;
            case 4:
                break;
            }
            break;
        case 3:
            clearviewport();
            mypoly(obj);
            break;
        case 4:
            break;
        }
    }
