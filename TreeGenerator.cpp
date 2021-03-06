#include "TreeGenerator.h"

TreeGenerator::TreeGenerator(std::string barkTexFilepath, std::string leafTexFilepath)
{
	barkTextureFile = barkTexFilepath;
	leafTextureFile = leafTexFilepath;
	srand(time(NULL));
	branch.init("c:\\Users\\Wilson\\Documents\\School\\CSE167\\PA4\\CSE167StarterCode-master\\cylinder2.obj");
	branch.heap = false;
	branch.addTexture(barkTexFilepath);
	leaf.init("c:\\Users\\Wilson\\Documents\\School\\CSE167\\PA4\\CSE167StarterCode-master\\sphere2.obj");
	leaf.heap = false;
}

TreeGenerator::~TreeGenerator()
{
}

Transform* TreeGenerator::generateTree(int levels)
{
	/*std::string X = "F[+B]F[-&B]F[-^B]FB";
	std::string F = "F";
	std::string B = "F[+B]F[-&B]F[-^B]";*/
	std::string X = "FF[+B]F[-&B]F[-^B]FB";
	std::string F = "FF";
	std::string B = "F[+B]F[-&B]F[-^B]FB";
	std::string tree(X);
	for (int i = 0; i < levels; ++i)
	{
		for(size_t pos = 0; (pos = tree.find_first_of("FB", pos)) != std::string::npos;)
		{
			switch (tree[pos])
			{
				case 'F':
				{
					tree.replace(pos, 1, F);
					pos += F.length();
					break;
				}
				case 'B':
				{
					tree.replace(pos, 1, B);
					pos +=B.length();
					break;
				}
			}
		}
	}
	if (levels)
	{
		int index = 0;
		return createTree(tree, index, levels, levels);
	}
	return NULL;
}

Transform* TreeGenerator::createTree(std::string rule, int& index, int level, int maxlevel)
{
	if (index >= rule.size())
	{
		return NULL;
	}
	bool done = false;
	Transform* newBranch = new Transform();
	while(!done && index < rule.size())
	{
		switch (rule[index])
		{
			case 'F':
			{
				Transform* branchTransform = new Transform();
				newBranch->translate(0, POTENTIAL(TRUNKHEIGHT, level, maxlevel), 0);
				branchTransform->scaleAbs(POTENTIALW(TRUNKWIDTH, level, maxlevel), POTENTIAL(TRUNKHEIGHT, level, maxlevel), POTENTIALW(TRUNKWIDTH, level, maxlevel));
				branchTransform->addChild(&branch);
				newBranch->addChild(branchTransform);
				done = true;
				break;
			}
			case 'B':
			{
				newBranch->addChild(&leaf);
				newBranch->translate(0, POTENTIAL(TRUNKHEIGHT, level + 1, maxlevel), 0);
				newBranch->rotate(X_AXIS_VEC, 90);
				done = true;
				break;
			}
			case '[':
			{
				Transform* subBranch = createTree(rule, ++index, level - 1, maxlevel);
				newBranch->addChild(subBranch);
				done = true;
				break;
			}
			case '+':
			{
				newBranch->rotate(Z_AXIS_VEC, Zturn + PLUSMINUS(20));
				if (isalpha(rule[index + 1]))
				{
					Transform* subBranch = createTree(rule, ++index, level, maxlevel);
					subBranch->translate(0, POTENTIALW(TRUNKWIDTH, level + 1, maxlevel) / 2.0f, 0);
					newBranch->addChild(subBranch);
					return newBranch;
				}
				else
				{
					++index;
				}
				break;
			}
			case '-':
			{
				newBranch->rotate(Z_AXIS_VEC, zturn + PLUSMINUS(20));
				if (isalpha(rule[index + 1]))
				{
					Transform* subBranch = createTree(rule, ++index, level, maxlevel);
					subBranch->translate(0, POTENTIALW(TRUNKWIDTH, level + 1, maxlevel) / 2.0f, 0);
					newBranch->addChild(subBranch);
					return newBranch;
				}
				else
				{
					++index;
				}
				break;
			}
			case '&':
			{
				newBranch->rotate(Y_AXIS_VEC, Yturn + PLUSMINUS(20));
				if (isalpha(rule[index + 1]))
				{
					Transform* subBranch = createTree(rule, ++index, level, maxlevel);
					subBranch->translate(0, POTENTIALW(TRUNKWIDTH, level + 1, maxlevel) / 2.0f, 0);
					newBranch->addChild(subBranch);
					return newBranch;
				}
				else
				{
					++index;
				}
				break;
			}
			case '^':
			{
				newBranch->rotate(Y_AXIS_VEC, yturn + PLUSMINUS(20));
				if (isalpha(rule[index + 1]))
				{
					Transform* subBranch = createTree(rule, ++index, level, maxlevel);
					subBranch->translate(0, POTENTIALW(TRUNKWIDTH, level + 1, maxlevel) / 2.0f, 0);
					newBranch->addChild(subBranch);
					return newBranch;
				}
				else
				{
					++index;
				}
				break;
			}
			default:
			{
				delete newBranch;
				done = true;
				return NULL;
			}
		}
	}
	if(index < rule.size())
	{
		Transform* subBranch = createTree(rule, ++index, level, maxlevel);
		newBranch->addChild(subBranch);
	}
/*	Transform* newBranch = new Transform();
	Transform* branchTransform = new Transform();
	newBranch->translate(0, POTENTIAL(TRUNKHEIGHT, level, maxlevel), 0);
	branchTransform->scaleAbs(POTENTIAL(TRUNKWIDTH, level, maxlevel), POTENTIAL(TRUNKHEIGHT, level, maxlevel), POTENTIAL(TRUNKWIDTH, level, maxlevel));
	branchTransform->addChild(&branch);
	newBranch->addChild(branchTransform);
	if(--level)
	{
		//left branch
		Transform* subBranch = createTree(level, maxlevel);
		subBranch->translate(0, POTENTIAL(TRUNKWIDTH, level + 1, maxlevel) / 2.0f, 0);
		Transform* subBranchRotate = new Transform();
		subBranchRotate->translate(0, POTENTIAL(TRUNKHEIGHT * 0.6f, level, maxlevel), 0);
		subBranchRotate->rotate(Z_AXIS_VEC, Zturn + PLUSMINUS(20));
		subBranchRotate->rotate(Y_AXIS_VEC, PLUSMINUS(20));
		subBranchRotate->addChild(subBranch);
		newBranch->addChild(subBranchRotate);

		//middle branch
		subBranch = createTree(level, maxlevel);
		subBranch->translate(0, POTENTIAL(TRUNKHEIGHT, level + 1, maxlevel) / 2.0f, 0);
		newBranch->addChild(subBranch);
		newBranch->addChild(createTree(level, maxlevel));

		//right branch
		subBranch = createTree(level, maxlevel);
		subBranch->translate(0, POTENTIAL(TRUNKWIDTH, level + 1, maxlevel) / 2.0f, 0);
		subBranchRotate = new Transform();
		subBranchRotate->translate(0, POTENTIAL(TRUNKHEIGHT * 0.2f, level, maxlevel), 0);
		subBranchRotate->rotate(Z_AXIS_VEC, zturn + PLUSMINUS(20));
		subBranchRotate->rotate(Y_AXIS_VEC, Yturn + PLUSMINUS(20));
		subBranchRotate->addChild(subBranch);
		newBranch->addChild(subBranchRotate);

		//front right branch
		subBranch = createTree(level, maxlevel);
		subBranch->translate(0, POTENTIAL(TRUNKWIDTH, level + 1, maxlevel) / 2.0f, 0);
		subBranchRotate = new Transform();
		subBranchRotate->translate(0, POTENTIAL(TRUNKHEIGHT * 0.2f, level, maxlevel), 0);
		subBranchRotate->rotate(Z_AXIS_VEC, zturn + PLUSMINUS(20));
		subBranchRotate->rotate(Y_AXIS_VEC, yturn - PLUSMINUS(20));
		subBranchRotate->addChild(subBranch);
		newBranch->addChild(subBranchRotate);
	}
	else
	{
		Transform* leaves = new Transform;
		leaves->addChild(&leaf);
		leaves->translate(0, POTENTIAL(TRUNKHEIGHT, level + 1, maxlevel), 0);
		leaves->rotate(X_AXIS_VEC, 90);
		newBranch->addChild(leaves);
	}*/
	return newBranch;
}
