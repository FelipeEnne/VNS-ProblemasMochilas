#include "header.h"

cEx2::cEx2()
{

	It0();
	SP(6);
	It1();
	SP(7);
	It2();
	SP(8);
	It3();
};

void cEx2::It0()
{
	try
	{
		GRBEnv *env = NULL;						// creates the GUROBI environment
		env = new GRBEnv();
		GRBModel model = GRBModel(*env);		// creates an empty model

		GRBVar l1 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l1");
		GRBVar l2 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l2");
		GRBVar l3 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l3");
		model.update();

		model.addConstr(550 * l1 + 630 * l2 + 630 * l3 <= 630, "c1");
		model.addConstr(416.667 * l1 +  521.667 * l2 + 509.1667 * l3 <= 600, "c2");


		model.addConstr(1 * l1 + 1 * l2  + 1 * l3 == 1, "c3");
		model.update();
		model.setObjective(-6800 * l1 - 5818 * l2 - 6373 * l3, GRB_MINIMIZE);
		model.update();
		model.write("MP6.lp");
		model.optimize();
		
		cout << "l2 = " << l2.get(GRB_DoubleAttr_X) << endl;
		cout << "l3 = " << l3.get(GRB_DoubleAttr_X) << endl;

		GRBConstr* c = 0;
		c = model.getConstrs();
		for (int i = 0; i < model.get(GRB_IntAttr_NumConstrs); ++i)
		{
			if (i == model.get(GRB_IntAttr_NumConstrs) - 1)
			{
				cout << "Pi0" << " = " << (double)c[i].get(GRB_DoubleAttr_Pi) << endl;//vetor p criar um ponteiro para o c recebe todas as restricoes 
			}
			else
			{
				cout << "Pi" << i + 1 << " = " << (double)c[i].get(GRB_DoubleAttr_Pi) << endl;
			}
		}
		cout << endl;
		//system("PAUSE");
	}
	catch (GRBException e)
	{
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
	}
	catch (...)
	{
		cout << "Exception during optimization" << endl;
	}

};


void cEx2::SP(int iteration)
{
	try
	{
		GRBEnv *env = NULL;						// creates the GUROBI environment
		env = new GRBEnv();
		GRBModel model = GRBModel(*env);		// creates an empty model

		GRBVar x1 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "x1");
		GRBVar x2 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "x2");
		model.update();

		int c1 = -10;
		int c2 = -9;

		model.addConstr(1 * x1 + 0.66666666666667 * x2 <= 708, "c1");
		model.addConstr(0.1 * x1 + 0.25 * x2 <= 135, "c2");
		model.update();

		double pi0;
		double pi1;
		double pi2;

		switch (iteration)
		{
		case 6:
			pi0 = -6800;
			pi1 = 0;
			pi2 = 0;
			break;
		case 7:
			//system("pause");
			pi0 = -2241.61;
			pi1 = -8.28799;
			//pi0 = 0;
			//pi1 = 0;
			pi2 = 0;
			break;
		case 8:
			//system("pause");
			pi0 = -4911.96;
			pi1 = -4.37457;
			//pi2 = 0;
			//pi0 = 0;
			//pi1 = 0;
			pi2 = 0;
			break;
		};

			GRBLinExpr pn = c1*x1 + c2*x2;
			GRBLinExpr rn1 = 0.7 * x1 + 1 * x2;
			GRBLinExpr rn2 = 0.5 * x1 + 0.8333 * x2;
			GRBLinExpr FO = pn - pi1*rn1 - pi2*rn2 - pi0;
			// cout << FO;
			//system("pause");
			model.setObjective(FO, GRB_MINIMIZE);
			model.update();
			model.write("SP" + to_string(iteration) + ".lp");
			model.optimize();

			cout << "x1 = " << x1.get(GRB_DoubleAttr_X) << endl;
			cout << "x2 = " << x2.get(GRB_DoubleAttr_X) << endl;


			cout << "r1 = " << 0.7 * x1.get(GRB_DoubleAttr_X) + x2.get(GRB_DoubleAttr_X)  << endl;
			cout << "r2 = " << 0.5 * x1.get(GRB_DoubleAttr_X) + 0.8333 * x2.get(GRB_DoubleAttr_X)  << endl;
			cout << "pn = " << c1*x1.get(GRB_DoubleAttr_X) + c2*x2.get(GRB_DoubleAttr_X) << endl;
			cout << "pnR = " << model.get(GRB_DoubleAttr_ObjVal)  << endl;//custo reduzido
			cout << endl;
			//system("PAUSE");

		}
		catch (GRBException e)
		{
			cout << "Error code = " << e.getErrorCode() << endl;
			cout << e.getMessage() << endl;
		}
		catch (...)
		{
			cout << "Exception during optimization" << endl;
		}
	};

void cEx2::It1()
{
	try
	{
		GRBEnv *env = NULL;						// creates the GUROBI environment
		env = new GRBEnv();
		GRBModel model = GRBModel(*env);		// creates an empty model

		GRBVar l1 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l1");
		GRBVar l2 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l2");
		GRBVar l3 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l3");
		GRBVar l4 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l4");
		model.update();

		model.addConstr(550 * l1 + 630 * l2 + 630 * l3 + 682.359 * l4 <= 630, "c1");
		model.addConstr(416.667 * l1 + 521.667 * l2 + 509.1667 * l3 + 529.077 * l4 <= 600, "c2");


		model.addConstr(1 * l1 + 1 * l2 + 1 * l3 + 1 * l4 == 1, "c3");
		model.update();
		model.setObjective(-6800 * l1 - 5818 * l2 - 6373 * l3 - 7896.99 * l4 , GRB_MINIMIZE);
		model.update();
		model.write("MP6.lp");
		model.optimize();

		cout << "l1 = " << l1.get(GRB_DoubleAttr_X) << endl;
		cout << "l2 = " << l2.get(GRB_DoubleAttr_X) << endl;
		cout << "l3 = " << l3.get(GRB_DoubleAttr_X) << endl;
		cout << "l4 = " << l4.get(GRB_DoubleAttr_X) << endl;

		GRBConstr* c = 0;
		c = model.getConstrs();
		for (int i = 0; i < model.get(GRB_IntAttr_NumConstrs); ++i)
		{
			if (i == model.get(GRB_IntAttr_NumConstrs) - 1)
			{
				cout << "Pi0" << " = " << (double)c[i].get(GRB_DoubleAttr_Pi) << endl;
			}
			else
			{
				cout << "Pi" << i + 1 << " = " << (double)c[i].get(GRB_DoubleAttr_Pi) << endl;
			}
		}
		cout << endl;
		//system("PAUSE");
	}
	catch (GRBException e)
	{
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
	}
	catch (...)
	{
		cout << "Exception during optimization" << endl;
	}

};

void cEx2::It2()
{
	try
	{
		GRBEnv *env = NULL;						// creates the GUROBI environment
		env = new GRBEnv();
		GRBModel model = GRBModel(*env);		// creates an empty model

		GRBVar l1 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l1");
		GRBVar l2 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l2");
		GRBVar l3 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l3");
		GRBVar l4 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l4");
		GRBVar l5 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l5");
		model.update();

		model.addConstr(550 * l1 + 630 * l2 + 630 * l3 + 682.359 * l4 + 495.6 * l5 <= 630, "c1");
		model.addConstr(416.667 * l1 + 521.667 * l2 + 509.1667 * l3 + 354 * l5 <= 600, "c2");


		model.addConstr(1 * l1 + 1 * l2 + 1 * l3 + 1 * l4 + 1 * l5 == 1, "c3");
		model.update();
		model.setObjective(-6800 * l1 - 5818 * l2 - 6373 * l3 - 7896.99 * l4 - 7080 * l5, GRB_MINIMIZE);
		model.update();
		model.write("MP6.lp");
		model.optimize();

		cout << "l1 = " << l1.get(GRB_DoubleAttr_X) << endl;
		cout << "l2 = " << l2.get(GRB_DoubleAttr_X) << endl;
		cout << "l3 = " << l3.get(GRB_DoubleAttr_X) << endl;
		cout << "l4 = " << l4.get(GRB_DoubleAttr_X) << endl;
		cout << "l5 = " << l5.get(GRB_DoubleAttr_X) << endl;

		GRBConstr* c = 0;
		c = model.getConstrs();
		for (int i = 0; i < model.get(GRB_IntAttr_NumConstrs); ++i)
		{
			if (i == model.get(GRB_IntAttr_NumConstrs) - 1)
			{
				cout << "Pi0" << " = " << (double)c[i].get(GRB_DoubleAttr_Pi) << endl;
			}
			else
			{
				cout << "Pi" << i + 1 << " = " << (double)c[i].get(GRB_DoubleAttr_Pi) << endl;
			}
		}
		cout << endl;
		//system("PAUSE");
	}
	catch (GRBException e)
	{
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
	}
	catch (...)
	{
		cout << "Exception during optimization" << endl;
	}

};

void cEx2::It3()
{
	try
	{
		GRBEnv *env = NULL;						// creates the GUROBI environment
		env = new GRBEnv();
		GRBModel model = GRBModel(*env);		// creates an empty model

		GRBVar l1 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l1");
		GRBVar l2 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l2");
		GRBVar l3 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l3");
		GRBVar l4 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l4");
		GRBVar l5 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l5");
		GRBVar l6 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "l6");
		model.update();

		model.addConstr(550 * l1 + 630 * l2 + 630 * l3 + 682.359 * l4 + 495.6 * l5 + 495.6 * l6 <= 630, "c1");
		model.addConstr(416.667 * l1 + 521.667 * l2 + 509.1667 * l3 + 354 * l5 + 354 * l6 <= 600, "c2");


		model.addConstr(1 * l1 + 1 * l2 + 1 * l3 + 1 * l4 + 1 * l5 + 1 * l6 == 1, "c3");
		model.update();
		model.setObjective(-6800 * l1 - 5818 * l2 - 6373 * l3 - 7896.99 * l4 - 7080 * l5 - 7080 * l6, GRB_MINIMIZE);
		model.update();
		model.write("MP6.lp");
		model.optimize();

		cout << "l1 = " << l1.get(GRB_DoubleAttr_X) << endl;
		cout << "l2 = " << l2.get(GRB_DoubleAttr_X) << endl;
		cout << "l3 = " << l3.get(GRB_DoubleAttr_X) << endl;
		cout << "l4 = " << l4.get(GRB_DoubleAttr_X) << endl;
		cout << "l5 = " << l5.get(GRB_DoubleAttr_X) << endl;
		cout << "l6 = " << l6.get(GRB_DoubleAttr_X) << endl;

		GRBConstr* c = 0;
		c = model.getConstrs();
		for (int i = 0; i < model.get(GRB_IntAttr_NumConstrs); ++i)
		{
			if (i == model.get(GRB_IntAttr_NumConstrs) - 1)
			{
				cout << "Pi0" << " = " << (double)c[i].get(GRB_DoubleAttr_Pi) << endl;
			}
			else
			{
				cout << "Pi" << i + 1 << " = " << (double)c[i].get(GRB_DoubleAttr_Pi) << endl;
			}
		}
		cout << endl;
		//system("PAUSE");
	}
	catch (GRBException e)
	{
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
	}
	catch (...)
	{
		cout << "Exception during optimization" << endl;
	}

};