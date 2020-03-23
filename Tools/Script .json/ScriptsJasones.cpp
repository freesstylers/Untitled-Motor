// ScriptsJasones.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{

    ofstream myfile;
    string inputString;
    int inputInt;
    float inputFloat;
    int vector3[3] = {};
    int vector4[4] = {};
    bool MeshAlready = false;

    cout << "Hola, buenas tardes, bienvenido al sistema de generacion de jasones para Motor Casa Paco\n";
   
    cout << "Indica el nombre del archivo que quieres crear\n";

    cin >> inputString;

    myfile.open(inputString + ".json");

    myfile << "{\n";

    //SceneName
    cout << "Indica el nombre de la escena\n";
    cin >> inputString;
    myfile << "\"name\" : \""+ inputString + "\",\n";

    //Camera Stuff
    myfile << "\"camera\" :\n";
    myfile << "{\n";

    cout << "Indica el nearClipDistance de la camara (INT)\n";
    cin >> inputString;
    myfile << "\"nearClipDistance\" : \"" + inputString + "\",\n";

    cout << "Indica el farClipDistance de la camara (INT)\n";
    cin >> inputString;
    myfile << "\"farClipDistance\" : \"" + inputString + "\",\n";

    cout << "Indica el autoAspectRatio de la camara (BOOL)\n";
    cin >> inputString;
    myfile << "\"autoAspectRatio\" : \"" + inputString + "\",\n";


    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
            cout << "Indica la posicion X de la camara (INT)\n";
        else if (i == 1)
            cout << "Indica la posicion Y de la camara (INT)\n";
        else
            cout << "Indica la posicion Z de la camara (INT)\n";

        cin >> inputInt;

        vector3[i] = inputInt;
    }

    myfile << "\"pos\" : ["+ to_string(vector3[0]) + ", " + to_string(vector3[1]) + ", " + to_string(vector3[2]) + "],\n";

    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
            cout << "Indica la posicion X del lookAt de la camara (INT)\n";
        else if (i == 1)
            cout << "Indica la posicion Y del lookAt de la camara (INT)\n";
        else
            cout << "Indica la posicion Z del lookAt de la camara (INT)\n";

        cin >> inputInt;

        vector3[i] = inputInt;
    }

    myfile << "\"lookAt\" : [" + to_string(vector3[0]) + ", " + to_string(vector3[1]) + ", " + to_string(vector3[2]) + "],\n";

    for (int i = 0; i < 4; i++)
    {
        if (i == 0)
            cout << "Indica el valor R del bgCoulour de la camara (INT)\n";
        else if (i == 1)
            cout << "Indica el valor G del bgCoulour de la camara (INT)\n";
        else if (i == 2)
            cout << "Indica el valor B del bgCoulour de la camara (INT)\n";
        else
            cout << "Indica el valor A del bgCoulour de la camara (INT)\n";

        cin >> inputInt;

        vector4[i] = inputInt;
    }

    myfile << "\"bgColour\" : [" + to_string(vector4[0]) + ", " + to_string(vector4[1]) + ", " + to_string(vector4[2]) + ", " + to_string(vector4[3]) +"]\n";
    
    myfile << "},\n";


    //Entities
    myfile << "\"entities\" :\n";
    
    myfile << "[\n";
    myfile << "{\n";

    cout << "Indica cuantas entidades hay en la escena\n";
    cin >> inputInt;

    for (int i = 0; i < inputInt; i++)
    {
        cout << "Indica el tipo de entidad\n";
        cout << "0 = Entidad definida sin prefab, con componentes a mano\n";
        //cout << "1 = Entidad definida con prefab\n"; //Pone que estan en proceso de implementacion
        //cout << "2 = Entidad definida con prefab, editando los componentes\n";

        cin >> inputInt;

        switch (inputInt)
        {
        case 0:

            //Tag
            cout << "Indica el tag del objeto\n";
            cin >> inputString;
            myfile << "\"tag\" : \"" + inputString + "\",\n";

            //Posicion
            for (int i = 0; i < 3; i++)
            {
                if (i == 0)
                    cout << "Indica la posicion X del objeto (INT)\n";
                else if (i == 1)
                    cout << "Indica la posicion Y del objeto (INT)\n";
                else
                    cout << "Indica la posicion Z del objeto (INT)\n";

                cin >> inputInt;

                vector3[i] = inputInt;
            }

            myfile << "\"position\" : [" + to_string(vector3[0]) + ", " + to_string(vector3[1]) + ", " + to_string(vector3[2]) + "],\n";

            //Rotacion
            for (int i = 0; i < 3; i++)
            {
                if (i == 0)
                    cout << "Indica la rotacion X del objeto (INT)\n";
                else if (i == 1)
                    cout << "Indica la rotacion Y del objeto (INT)\n";
                else
                    cout << "Indica la rotacion Z del objeto (INT)\n";

                cin >> inputInt;

                vector3[i] = inputInt;
            }

            myfile << "\"rotation\" : [" + to_string(vector3[0]) + ", " + to_string(vector3[1]) + ", " + to_string(vector3[2]) + "],\n";


            //Escala
            for (int i = 0; i < 3; i++)
            {
                if (i == 0)
                    cout << "Indica la escala X del objeto (INT)\n";
                else if (i == 1)
                    cout << "Indica la escala Y del objeto (INT)\n";
                else
                    cout << "Indica la escala Z del objeto (INT)\n";

                cin >> inputInt;

                vector3[i] = inputInt;
            }

            myfile << "\"scale\" : [" + to_string(vector3[0]) + ", " + to_string(vector3[1]) + ", " + to_string(vector3[2]) + "],\n";

            //Componentes
            myfile << "\"components\" :[\n";
            cout << "Indica el tipo de componente [Mesh\Rigidbody]\n";
            cin >> inputString;

            //Mesh
            if (inputString == "Mesh" || inputString == "Rigidbody" && !MeshAlready)
            {
                MeshAlready = true;

                if (inputString == "Rigidbody")
                    cout << "Hace falta una Mesh antes del Rigidbody, asi que va antes\n";

                myfile << "\"type\" : \"Mesh\",\n";

                cout << "Indica el nombre del archivo de la Mesh\n";
                cin >> inputString;
                myfile << "\"mesh\" : \"" + inputString + ".mesh\",\n";

                cout << "Indica el nombre del material\n";
                cin >> inputString;
                myfile << "\"material\" : \"" + inputString + "\",\n";
                
                cout << "Indica si esta animado [BOOL]\n";
                cin >> inputString;
                myfile << "\"isAnimated\" : \"" + inputString + "\",\n";
                myfile << "},\n";
            }

            //Rigidbody
            if (inputString == "Rigidbody" && MeshAlready)
            {
                bool isStatic = false;
                bool isKinematic = false;

                myfile << "{\n";
                myfile << "\"type\" : \"RigidBody\",\n";
                
                cout << "Indica la forma de la shape [Sphere/Cube/Mesh]\n";
                cin >> inputString;
                myfile << "\"shape\" : \"" + inputString + "\",\n";

                cout << "Indica si es estatico [BOOL]\n";
                cin >> inputString;
                if (inputString == "true")
                {
                    isStatic = true;
                    myfile << "\"isStatic\" : \"" + inputString + "\",\n";
                }

                if (!isStatic)
                {
                    cout << "Indica si es kinematico [BOOL]\n";
                    cin >> inputString;
                    if (inputString == "true")
                    {
                        isKinematic = true;
                        myfile << "\"isKinematic\" : \"" + inputString + "\",\n";
                    }
                }

                if (isStatic || isKinematic)
                {
                    cout << "Indica la masa del objeto [FLOAT]\n";
                    cin >> inputFloat;
                    myfile << "\"mass\" : \"" + to_string(inputFloat) + "\",\n";
                }
            }
            break;
        default:
            break;
        }
    }

    myfile.close();

    return 0;
}
