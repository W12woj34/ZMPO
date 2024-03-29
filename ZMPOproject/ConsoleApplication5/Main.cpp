// ConsoleApplication5.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include "pch.h"
#include "Main.h"


int main()
{
	vRun();

	return 0;
}

void vRun()
{
	srand(time(NULL));

	std::vector<double> c_values;
	std::vector<double> c_weights;
	std::vector<double> c_maxItems;

	c_values.push_back(c_ITEM_1_VALUE);
	c_values.push_back(c_ITEM_2_VALUE);
	c_values.push_back(c_ITEM_3_VALUE);
	c_values.push_back(c_ITEM_4_VALUE);
	c_values.push_back(c_ITEM_5_VALUE);
	c_values.push_back(c_ITEM_6_VALUE);
	c_values.push_back(c_ITEM_7_VALUE);
	c_values.push_back(c_ITEM_8_VALUE);
	c_values.push_back(c_ITEM_9_VALUE);
	c_values.push_back(c_ITEM_10_VALUE);
	c_values.push_back(c_ITEM_11_VALUE);
	c_values.push_back(c_ITEM_12_VALUE);
	c_values.push_back(c_ITEM_13_VALUE);
	c_values.push_back(c_ITEM_14_VALUE);
	c_values.push_back(c_ITEM_15_VALUE);
	c_values.push_back(c_ITEM_16_VALUE);
	c_values.push_back(c_ITEM_17_VALUE);
	c_values.push_back(c_ITEM_18_VALUE);
	c_values.push_back(c_ITEM_19_VALUE);
	c_values.push_back(c_ITEM_20_VALUE);

	c_weights.push_back(c_ITEM_1_WEIGHT);
	c_weights.push_back(c_ITEM_2_WEIGHT);
	c_weights.push_back(c_ITEM_3_WEIGHT);
	c_weights.push_back(c_ITEM_4_WEIGHT);
	c_weights.push_back(c_ITEM_5_WEIGHT);
	c_weights.push_back(c_ITEM_6_WEIGHT);
	c_weights.push_back(c_ITEM_7_WEIGHT);
	c_weights.push_back(c_ITEM_8_WEIGHT);
	c_weights.push_back(c_ITEM_9_WEIGHT);
	c_weights.push_back(c_ITEM_10_WEIGHT);
	c_weights.push_back(c_ITEM_11_WEIGHT);
	c_weights.push_back(c_ITEM_12_WEIGHT);
	c_weights.push_back(c_ITEM_13_WEIGHT);
	c_weights.push_back(c_ITEM_14_WEIGHT);
	c_weights.push_back(c_ITEM_15_WEIGHT);
	c_weights.push_back(c_ITEM_16_WEIGHT);
	c_weights.push_back(c_ITEM_17_WEIGHT);
	c_weights.push_back(c_ITEM_18_WEIGHT);
	c_weights.push_back(c_ITEM_19_WEIGHT);
	c_weights.push_back(c_ITEM_20_WEIGHT);

	c_maxItems.push_back(c_ITEM_1_MAX);
	c_maxItems.push_back(c_ITEM_2_MAX);
	c_maxItems.push_back(c_ITEM_3_MAX);
	c_maxItems.push_back(c_ITEM_4_MAX);
	c_maxItems.push_back(c_ITEM_5_MAX);
	c_maxItems.push_back(c_ITEM_6_MAX);
	c_maxItems.push_back(c_ITEM_7_MAX);
	c_maxItems.push_back(c_ITEM_8_MAX);
	c_maxItems.push_back(c_ITEM_9_MAX);
	c_maxItems.push_back(c_ITEM_10_MAX);
	c_maxItems.push_back(c_ITEM_11_MAX);
	c_maxItems.push_back(c_ITEM_12_MAX);
	c_maxItems.push_back(c_ITEM_13_MAX);
	c_maxItems.push_back(c_ITEM_14_MAX);
	c_maxItems.push_back(c_ITEM_15_MAX);
	c_maxItems.push_back(c_ITEM_16_MAX);
	c_maxItems.push_back(c_ITEM_17_MAX);
	c_maxItems.push_back(c_ITEM_18_MAX);
	c_maxItems.push_back(c_ITEM_19_MAX);
	c_maxItems.push_back(c_ITEM_20_MAX);

	CMenu *menu = new CMenu(c_MENU_MAIN, c_MAIN, c_EMPTY, nullptr);
	CMenu *pod1 = new CMenu(c_SUBMENU_1, c_SUB_1, menu->sGetPath(), menu);
	CMenu *pod2 = new CMenu(c_SUBMENU_2, c_SUB_2, menu->sGetPath(), menu);
	CMenu *pod3 = new CMenu(c_SUBMENU_3, c_SUB_3, pod2->sGetPath(), pod2);

	menu->c_getCMenuList()->push_back(pod1);
	menu->c_getCMenuList()->push_back(pod2);
	pod2->c_getCMenuList()->push_back(pod3);

	menu->vAddCMenuItem(new CMenuCommand(c_NAME_INT, c_INT, menu->sGetPath(), c_HELP_1, menu, new CCommandAlgorithmInt(c_values, c_weights, c_maxItems)));
	menu->vAddCMenuItem(new CMenuCommand(c_NAME_DOUBLE, c_DOUBLE, menu->sGetPath(), c_HELP_2, menu, new CCommandAlgorithmDouble(c_values, c_weights, c_maxItems)));
	menu->vAddCMenuItem(new CMenuCommand(c_NAME_BOOL, c_BOOL, menu->sGetPath(), c_HELP_3, menu, new CCommandAlgorithmBool(c_values, c_weights)));
	
	menu->vRun();
	delete menu;
}



