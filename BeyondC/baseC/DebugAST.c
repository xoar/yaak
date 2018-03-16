#include "DebugAST.h"

void printTree( NODEPTR node)
{
	printf("node prod is %d\n", node->_prod);

	for (int i =0; i < node->childs.size(); i++)
	{
		printTree(node->childs[i]);

	}

}


void debugAST()
{
      NODEPTR topNode;
      topNode = _nodestacktop;

#ifdef __cplusplus
      if (topNode != NULLNODEPTR)
      {
      	printTree(topNode);
      	/*printf("\ntopNode prod is %d\n", topNode->_prod);
      	printf("\ntopNode child count is %d\n", topNode->childs.size());*/

      }
      else
      {
      	printf("\nKein top node\n");
      }
#endif

}