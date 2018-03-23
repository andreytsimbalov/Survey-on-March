
#include "../src/nn.h"
#include "../src/survey.h"

#include "testutil.h"

#define SOCKET_ADDRESS "inproc://test"

int main ()
{
    int rc;
    int surveyor;
    int respondent1;
    int respondent2;
    int respondent3;
    int deadline = 10000;
    char buf [7];
	char text="ABC";



    //“ест простого survey с трем€ клиентами
    surveyor = test_socket (AF_SP, NN_SURVEYOR);
    deadline = 500;
    rc = nn_setsockopt (surveyor, NN_SURVEYOR, NN_SURVEYOR_DEADLINE, &deadline, sizeof (deadline));
    errno_assert (rc == 0);
    test_bind (surveyor, SOCKET_ADDRESS);
		printf("Serv connect inproc://test      ");
    respondent1 = test_socket (AF_SP, NN_RESPONDENT);
    test_connect (respondent1, SOCKET_ADDRESS);
		printf("r1 connect inproc://test       ");
    respondent2 = test_socket (AF_SP, NN_RESPONDENT);
    test_connect (respondent2, SOCKET_ADDRESS);
		printf("r2 connect inproc://test       ");
    respondent3 = test_socket (AF_SP, NN_RESPONDENT);
    test_connect (respondent3, SOCKET_ADDRESS);
		printf("r3 connect inproc://test       ");

    
    rc = nn_recv (surveyor, buf, sizeof (buf), 0);
    errno_assert (rc == -1 && nn_errno () == EFSM);

    //отправка опроса
    test_send (surveyor, &text);
	
		printf("S: ABC         ");
    //первый клиент отвечает
    test_recv (respondent1, &text);
    test_send (respondent1, "DEF");
		printf("r1: ABC ");
		printf("- DEF          ");
		//второй клиент отвечает
    test_recv (respondent2, &text);
    test_send (respondent2, "DEF");
		printf("r2: ABC ");
		printf("- DEF          ");
    //опросник принимает ответы
    test_recv (surveyor, "DEF");
    test_recv (surveyor, "DEF");
		printf("S: DEF           ");
    //Ѕольше ответов опросник не принимает, дедлайн закончилс€
    rc = nn_recv (surveyor, buf, sizeof (buf), 0);
    errno_assert (rc == -1 && nn_errno () == ETIMEDOUT);

	//третий клиент отвечает (но он уже не уложилс€ в дедлайн, увы)
    test_recv (respondent3, &text);
    test_send (respondent3, "GHI");
		printf("r3: ABC ");
		printf("- GHI           ");
    // ќпросник работает еЄ раз
    test_send (surveyor, &text);
		printf("S: ABC                           ");
    // Ќеобходимо убедитьс€, что ответ от третьего клиента не доставлен
    rc = nn_recv (surveyor, buf, sizeof (buf), 0);
    errno_assert (rc == -1 && nn_errno () == ETIMEDOUT);

    
    rc = nn_recv (surveyor, buf, sizeof (buf), 0);
    errno_assert (rc == -1 && nn_errno () == EFSM);
	
    test_close (surveyor);
    test_close (respondent1);
    test_close (respondent2);
    test_close (respondent3);
	nn_sleep(10000);
		printf(" End");
	nn_sleep(1000);
    return 0;
}

