////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 使用 A* 算法来解决24数码问题
//
// Created by Shengjia Yan @2016-5-12
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <new>
#include <iomanip>
#include <utility>
#include <vector>
#include <fstream>

#include <ctype.h>

using namespace std;

// 配置
#define NUM_TIMES_TO_RUN_SEARCH 1
#define DISPLAY_SOLUTION_FORWARDS 1		// 显示前向步骤
#define DISPLAY_SOLUTION_BACKWARDS 0	// 显示后向步骤
#define DISPLAY_SOLUTION_INFO 1
#define DEBUG_LISTS 0					// 显示 DEBUG 列表

// Astar 搜索类
#include "stlastar.h" // 查看头文件来获取版权信息和使用信息

// 全局变量
#define BOARD_WIDTH   (5)
#define BOARD_HEIGHT  (5)
#define GM_TILE       (-1)
#define GM_SPACE	  (0)
#define GM_OFF_BOARD  (1)

vector<pair<int, int> > Move;

// 定义

// 定义以下函数，来使用 Astar搜索类

// 数据
//		Your own state space information
// 函数
//		(Optional) Constructor.
//		Nodes are created by the user, so whether you use a
//      constructor with parameters as below, or just set the object up after the 
//      constructor, is up to you.
//
//		(Optional) Destructor. 
//		The destructor will be called if you create one. You 
//		can rely on the default constructor unless you dynamically allocate something in
//		your data
//
//		float GoalDistanceEstimate( PuzzleState &nodeGoal );
//		Return the estimated cost to goal from this node (pass reference to goal node)
//
//		bool IsGoal( PuzzleState &nodeGoal );
//		Return true if this node is the goal.
//
//		bool GetSuccessors( AStarSearch<PuzzleState> *astarsearch );
//		For each successor to this state call the AStarSearch's AddSuccessor call to 
//		add each one to the current search - return false if you are out of memory and the search
//		will fail
//
//		float GetCost( PuzzleState *successor );
//		Return the cost moving from this state to the state of successor
//
//		bool IsSameState( PuzzleState &rhs );
//		Return true if the provided state is the same as this state

// Here the example is the 24-puzzle state ...
// 24-数码的状态
class PuzzleState
{

public:

	// 定义
	typedef enum
	{
		TL_SPACE,   // 0
		TL_1, 
		TL_2,  
		TL_3, 
		TL_4, 
		TL_5, 
		TL_6, 
		TL_7, 
		TL_8,
        TL_9,
        TL_10,
        TL_11,
        TL_12,
        TL_13,
        TL_14,
        TL_15,
        TL_16,
        TL_17,
        TL_18,
        TL_19,
        TL_20,
        TL_21,
        TL_22,
        TL_23,
        TL_24,
	} TILE;

	// 数据
	static TILE g_goal[ BOARD_WIDTH*BOARD_HEIGHT];      // 目标状态
	static TILE g_start[ BOARD_WIDTH*BOARD_HEIGHT];     // 初始状态

	// the tile data for the 24-puzzle
    // 24-数码的方块数据
	TILE tiles[ BOARD_WIDTH*BOARD_HEIGHT ];

	// 成员函数

	PuzzleState() {  
						memcpy( tiles, g_goal, sizeof( TILE ) * BOARD_WIDTH * BOARD_HEIGHT );			
					}

	PuzzleState( TILE *param_tiles ) 
					{
						memcpy( tiles, param_tiles, sizeof( TILE ) * BOARD_WIDTH * BOARD_HEIGHT );			
					}

	float GoalDistanceEstimate( PuzzleState &nodeGoal );
	bool IsGoal( PuzzleState &nodeGoal );
	bool GetSuccessors( AStarSearch<PuzzleState> *astarsearch, PuzzleState *parent_node );
	float GetCost( PuzzleState &successor );
	bool IsSameState( PuzzleState &rhs );
	
	void PrintNodeInfo();
	void WriteNodeInfo();

private:
	// User stuff - Just add what you need to help you write the above functions...
    // 用户的东西 - 随意添加你需要的函数来实现你的功能

	void GetSpacePosition( PuzzleState *pn, int *rx, int *ry );
	bool LegalMove( TILE *StartTiles, TILE *TargetTiles, int spx, int spy, int tx, int ty );
	int GetMap( int x, int y, TILE *tiles );

};


// 目标状态
PuzzleState::TILE PuzzleState::g_goal[] = 
{
	TL_1,  TL_2,  TL_3,  TL_4,  TL_5,
    TL_16, TL_17, TL_18, TL_19, TL_6, 
    TL_15, TL_24, TL_SPACE, TL_20, TL_7, 
    TL_14, TL_23, TL_22, TL_21, TL_8, 
    TL_13, TL_12, TL_11, TL_10, TL_9
};

// 一些好的初始状态
PuzzleState::TILE PuzzleState::g_start[] = 
{

#if 0
	// ex a -  2 steps
	TL_1,  TL_2,  TL_3,  TL_4,  TL_5,
    TL_16, TL_17, TL_18, TL_19, TL_6, 
    TL_15, TL_24, TL_20, TL_7, TL_SPACE,
    TL_14, TL_23, TL_22, TL_21, TL_8, 
    TL_13, TL_12, TL_11, TL_10, TL_9

#elif 0
	// ex b -  4 steps
	TL_1,  TL_2,  TL_3,  TL_4,  TL_5,
    TL_16, TL_17, TL_18, TL_19, TL_6, 
    TL_15, TL_24, TL_20, TL_7, TL_8,
    TL_14, TL_23, TL_22, TL_21, TL_9, 
    TL_13, TL_12, TL_11, TL_10, TL_SPACE


#elif 1
	// ex c -  12000 steps
	TL_1,  TL_3,  TL_4,  TL_19, TL_5,
	TL_16, TL_2,  TL_18, TL_6,  TL_7,
	TL_24, TL_17, TL_20, TL_21, TL_8,
	TL_15, TL_14, TL_22, TL_11, TL_10,
	TL_13, TL_23, TL_12, TL_9,  TL_SPACE


#elif 0
	// nasty one - doesn't solve


#endif  

};

// 判断棋盘状态是否相同
bool PuzzleState::IsSameState( PuzzleState &rhs )
{

	for( int i=0; i<(BOARD_HEIGHT*BOARD_WIDTH); i++ )
	{
		if( tiles[i] != rhs.tiles[i] )
		{
			return false;
		}
	}

	return true;

}


// 打印节点信息 整个棋盘就是一个“节点”
void PuzzleState::PrintNodeInfo()
{
	cout<<setiosflags(ios::left);
	cout<<setw(3)<<tiles[0]<<setw(3)<<tiles[1]<<setw(3)<<tiles[2]<<setw(3)<<tiles[3]<<setw(3)<<tiles[4]<<endl;
	cout<<setw(3)<<tiles[5]<<setw(3)<<tiles[6]<<setw(3)<<tiles[7]<<setw(3)<<tiles[8]<<setw(3)<<tiles[9]<<endl;
	cout<<setw(3)<<tiles[10]<<setw(3)<<tiles[11]<<setw(3)<<tiles[12]<<setw(3)<<tiles[13]<<setw(3)<<tiles[14]<<endl;
	cout<<setw(3)<<tiles[15]<<setw(3)<<tiles[16]<<setw(3)<<tiles[17]<<setw(3)<<tiles[18]<<setw(3)<<tiles[19]<<endl;
	cout<<setw(3)<<tiles[20]<<setw(3)<<tiles[21]<<setw(3)<<tiles[22]<<setw(3)<<tiles[23]<<setw(3)<<tiles[24]<<endl;
	
	int x,y;

	for( y=0; y<BOARD_HEIGHT; y++ )
	{
		for( x=0; x<BOARD_WIDTH; x++ )
		{
			if( tiles[(y*BOARD_WIDTH)+x] == TL_SPACE )
			{
				// 记录空白格运动路径
				Move.push_back(make_pair(x, y));
			}
		}
	}
	
}

// 输出节点信息到文件
void PuzzleState::WriteNodeInfo()
{
	ofstream out("24puzzle_start.txt");
	out<<tiles[0]<<" "<<tiles[1]<<" "<<tiles[2]<<" "<<tiles[3]<<" "<<tiles[4]<<" ";
	out<<tiles[5]<<" "<<tiles[6]<<" "<<tiles[7]<<" "<<tiles[8]<<" "<<tiles[9]<<" ";
	out<<tiles[10]<<" "<<tiles[11]<<" "<<tiles[12]<<" "<<tiles[13]<<" "<<tiles[14]<<" ";
	out<<tiles[15]<<" "<<tiles[16]<<" "<<tiles[17]<<" "<<tiles[18]<<" "<<tiles[19]<<" ";
	out<<tiles[20]<<" "<<tiles[21]<<" "<<tiles[22]<<" "<<tiles[23]<<" "<<tiles[24]<<endl;
}




// Here's the heuristic function that estimates the distance from a PuzzleState
// to the Goal. 
// 这是用于估计当前棋盘状态和目标状态之间的距离的启发式函数，返回当前节点的启发式分数 h

float PuzzleState::GoalDistanceEstimate( PuzzleState &nodeGoal )
{

	// Nilsson's sequence score 尼尔森序列分数

	int i, cx, cy, ax, ay;	// i: 迭代器 cx,cy: 方块目标位置 ax,ay: 方块当前位置
	int h = 0;	// 启发式分数
	int s, t;	// s分数 t分数

	// given a tile this returns the tile that should be clockwise
	// 给定一个方块，返回它顺时针方向上第一个方块
	TILE correct_follower_to[ BOARD_WIDTH * BOARD_HEIGHT ] =
	{
		/*
			1  2  3  4  5
			16 17 18 19 6
			15 24    20 7
			14 23 22 21 8
			13 12 11 10 9
		*/
		/* TL_SPACE */ TL_SPACE, // 空格会出错，不考虑空格	
		/* TL_1 */ TL_2,
		/* TL_2 */ TL_3,
		/* TL_3 */ TL_4,
		/* TL_4 */ TL_5,
		/* TL_5 */ TL_6,
		/* TL_6 */ TL_7,
		/* TL_7 */ TL_8,
		/* TL_8 */ TL_9,
		/* TL_9 */ TL_10,
		/* TL_10 */ TL_11,
		/* TL_11 */ TL_12,
		/* TL_12 */ TL_13,
		/* TL_13 */ TL_14,
		/* TL_14 */ TL_15,
		/* TL_15 */ TL_16,
		/* TL_16 */ TL_1,
		/* TL_17 */ TL_18,
		/* TL_18 */ TL_19,
		/* TL_19 */ TL_20,
		/* TL_20 */ TL_21,
		/* TL_21 */ TL_22,
		/* TL_22 */ TL_23,
		/* TL_23 */ TL_24,
		/* TL_24 */ TL_17
	};

	// given a table index returns the index of the tile that is clockwise to it 3*3 only
	// 给定一个表的索引，返回它顺时针方向上第一个方块的索引
	int clockwise_tile_of[ BOARD_WIDTH * BOARD_HEIGHT ] =
	{
		/*
			0  1  2  3  4
			5  6  7  8  9
			10 11 12 13 14
			15 16 17 18 19
			20 21 22 23 24
		*/
		1,	// 0
		2,  // 1	  
		3,	// 2   
		4,  // 3
		9,	// 4
		0,	// 5
		7,	// 6
		8,	// 7
		13,	// 8
		14,	// 9
		5,	// 10
		6,	// 11
		-1,	// 12 中心方块不会被叫到
		18,	// 13
		19,	// 14
		10,	// 15
		11,	// 16
		16,	// 17
		17,	// 18
		24,	// 19
		15,	// 20
		20,	// 21
		21,	// 22
		22,	// 23
		23	// 24
	};

	// 方块的目标位置的x坐标
	int tile_x[ BOARD_WIDTH * BOARD_HEIGHT ] =
	{
		/* TL_SPACE */ 2,
		/* TL_1 */ 0,    
		/* TL_2 */ 1,    
		/* TL_3 */ 2,    
		/* TL_4 */ 4,    
		/* TL_5 */ 2,    
		/* TL_6 */ 4,    
		/* TL_7 */ 4,    
		/* TL_8 */ 4,    
		/* TL_9 */ 4,
		/* TL_10 */ 3,
		/* TL_11 */ 2,
		/* TL_12 */ 1,
		/* TL_13 */ 0,
		/* TL_14 */ 0,
		/* TL_15 */ 0,
		/* TL_16 */ 0,
		/* TL_17 */ 1,
		/* TL_18 */ 2,
		/* TL_19 */ 3,
		/* TL_20 */ 3,
		/* TL_21 */ 3,
		/* TL_22 */ 2,
		/* TL_23 */ 1,
		/* TL_24 */ 1
	};

	// 方块的目标位置的y坐标
	int tile_y[ BOARD_WIDTH * BOARD_HEIGHT ] =
	{
		/* TL_SPACE */ 2,	
		/* TL_1 */ 0,
		/* TL_2 */ 0,
		/* TL_3 */ 0,
		/* TL_4 */ 0,
		/* TL_5 */ 0,
		/* TL_6 */ 1,
		/* TL_7 */ 2,
		/* TL_8 */ 3,
		/* TL_9 */ 4,
		/* TL_10 */ 4,
		/* TL_11 */ 4,
		/* TL_12 */ 4,
		/* TL_13 */ 4,
		/* TL_14 */ 3,
		/* TL_15 */ 2,
		/* TL_16 */ 1,
		/* TL_17 */ 1,
		/* TL_18 */ 1,
		/* TL_19 */ 1,
		/* TL_20 */ 2,
		/* TL_21 */ 3,
		/* TL_22 */ 3,
		/* TL_23 */ 3,
		/* TL_24 */ 2
	};

	s=0;
	
	// score 1 point if centre is not correct 
	// 假如当前棋盘中心和目标状态的中心不匹配，得1分
	if( tiles[(BOARD_HEIGHT*BOARD_WIDTH)/2] != nodeGoal.tiles[(BOARD_HEIGHT*BOARD_WIDTH)/2] )
	{
 		s = 1;
	}

	for( i=0; i<(BOARD_HEIGHT*BOARD_WIDTH); i++ )
	{
		// this loop adds up the totaldist element in h and
		// the sequence score in s

		// the space does not count 空格不算
		if( tiles[i] == TL_SPACE )
		{
			continue;
		}

		// get correct x and y of this tile	
		// 获取该方块的目标位置
		cx = tile_x[tiles[i]];
		cy = tile_y[tiles[i]];

		// get actual	
		ax = i % BOARD_WIDTH;
		ay = i / BOARD_WIDTH;

		// add manhatten distance to h
		// 计算 manhatten 距离加到 h 上
		h += abs( cx-ax );
		h += abs( cy-ay );

		// no s score for center tile
		// 中心方块不用计算 s分数
		if( (ax == (BOARD_WIDTH/2)) && (ay == (BOARD_HEIGHT/2)) )
		{
			continue;
		}

		// score 2 points if not followed by successor
		// 假如当前方块顺时针方向上的第一个方块不是目标状态中它顺时针方向上第一个方块，那么 s 得2分
		if( correct_follower_to[ tiles[i] ] != tiles[ clockwise_tile_of[ i ] ] )
		{
			// clockwise_tile_of[i]是索引为i的方块顺时针方向上第一个方块
			s += 2;
		}


	}

	// mult by 3 and add to h
	// s乘3再加h
	t = h + (3*s);
	
	return (float) t;	// 返回当前节点的启发式分数 h

}


// 判断当前棋盘状态是否达到目标状态
bool PuzzleState::IsGoal( PuzzleState &nodeGoal )
{
	return IsSameState( nodeGoal );
}

// Helper
// Return the x and y position of the space tile
// 返回空白方块的位置
void PuzzleState::GetSpacePosition( PuzzleState *pn, int *rx, int *ry )
{
	int x,y;

	for( y=0; y<BOARD_HEIGHT; y++ )
	{
		for( x=0; x<BOARD_WIDTH; x++ )
		{
			if( pn->tiles[(y*BOARD_WIDTH)+x] == TL_SPACE )
			{
				*rx = x;
				*ry = y;

				return;
			}
		}
	}


	assert( false && "Something went wrong. There's no space on the board" );

}

int PuzzleState::GetMap( int x, int y, TILE *tiles )
{

	if( x < 0 ||
	    x >= BOARD_WIDTH ||
		 y < 0 ||
		 y >= BOARD_HEIGHT
	  )
		return GM_OFF_BOARD;	 

	if( tiles[(y*BOARD_WIDTH)+x] == TL_SPACE )
	{
		return GM_SPACE;
	}

	return GM_TILE;
}

// Given a node set of tiles and a set of tiles to move them into, do the move as if it was on a tile board
// note : returns false if the board wasn't changed, and simply returns the tiles as they were in the target
// spx and spy is the space position while tx and ty is the target move from position

bool PuzzleState::LegalMove( TILE *StartTiles, TILE *TargetTiles, int spx, int spy, int tx, int ty )
{

	int t;
	
	if( GetMap( spx, spy, StartTiles ) == GM_SPACE )
	{
		if( GetMap( tx, ty, StartTiles ) == GM_TILE )
		{

			// 拷贝瓦片
			for( t=0; t<(BOARD_HEIGHT*BOARD_WIDTH); t++ )
			{
				TargetTiles[t] = StartTiles[t];
			}

			TargetTiles[ (ty*BOARD_WIDTH)+tx ] = StartTiles[ (spy*BOARD_WIDTH)+spx ];
			TargetTiles[ (spy*BOARD_WIDTH)+spx ] = StartTiles[ (ty*BOARD_WIDTH)+tx ];
			
			return true;
		}
	}
	return false;

}

// This generates the successors to the given PuzzleState. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool PuzzleState::GetSuccessors( AStarSearch<PuzzleState> *astarsearch, PuzzleState *parent_node )
{
	PuzzleState NewNode;

	int sp_x,sp_y;

	GetSpacePosition( this, &sp_x, &sp_y );

	bool ret;

	if( LegalMove( tiles, NewNode.tiles, sp_x, sp_y, sp_x, sp_y-1 ) == true )
	{
		ret = astarsearch->AddSuccessor( NewNode );
		
		if( !ret ) return false;
	}

	if( LegalMove( tiles, NewNode.tiles, sp_x, sp_y, sp_x, sp_y+1 ) == true )
	{
		ret = astarsearch->AddSuccessor( NewNode );
		
		if( !ret ) return false;
	}

	if( LegalMove( tiles, NewNode.tiles, sp_x, sp_y, sp_x-1, sp_y ) == true )
	{
		ret = astarsearch->AddSuccessor( NewNode );

		if( !ret ) return false;
	}

	if( LegalMove( tiles, NewNode.tiles, sp_x, sp_y, sp_x+1, sp_y ) == true )
	{
		ret = astarsearch->AddSuccessor( NewNode );

		if( !ret ) return false;
	}

	return true; 
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is 
// conceptually where we're moving
float PuzzleState::GetCost( PuzzleState &successor )
{
	return 1.0f; // I love it when life is simple

}


// Main

int main( int argc, char *argv[] )
{	
	cout << "A* 24-puzzle solver implementation\n@2016 Shengjia Yan\n";

	if( argc > 1 )
	{
		int i = 0;
		int c;

		while( (c = argv[1][i]) )
		{
			if( isdigit( c ) )
			{
				int num = (c - '0');

				PuzzleState::g_start[i] = static_cast<PuzzleState::TILE>(num);
				
			}
		
			i++;
		}


	}

	// Create an instance of the search class...
	// 创建搜索类的一个实例

	AStarSearch<PuzzleState> astarsearch;

	int NumTimesToSearch = NUM_TIMES_TO_RUN_SEARCH;	// 运行搜索的次数：1次

	while( NumTimesToSearch-- )
	{

		// 创建初始状态
		PuzzleState nodeStart( PuzzleState::g_start );

		// 定义目标状态
		PuzzleState nodeEnd( PuzzleState::g_goal );

		// 设置初始状态和目标状态
		astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

		unsigned int SearchState;

		unsigned int SearchSteps = 0;

		do
		{
			SearchState = astarsearch.SearchStep();

#if DEBUG_LISTS

			float f,g,h;
			
			cout << "搜索步数： " << SearchSteps << endl;

			cout << "Open:\n";
			PuzzleState *p = astarsearch.GetOpenListStart( f,g,h );
			while( p )
			{
				((PuzzleState *)p)->PrintNodeInfo();
				cout << "f: " << f << " g: " << g << " h: " << h << "\n\n";
				
				p = astarsearch.GetOpenListNext( f,g,h );
				
			}

			cout << "Closed:\n";
			p = astarsearch.GetClosedListStart( f,g,h );
			while( p )
			{
				p->PrintNodeInfo();
				cout << "f: " << f << " g: " << g << " h: " << h << "\n\n";
				
				p = astarsearch.GetClosedListNext( f,g,h );
			}

#endif

// Test cancel search
#if 0
			int StepCount = astarsearch.GetStepCount();
			if( StepCount == 10 )
			{
				astarsearch.CancelSearch();
			}
#endif
			SearchSteps++;
		}
		while( SearchState == AStarSearch<PuzzleState>::SEARCH_STATE_SEARCHING );

		if( SearchState == AStarSearch<PuzzleState>::SEARCH_STATE_SUCCEEDED )
		{
#if DISPLAY_SOLUTION_FORWARDS	// 显示前向步骤
			cout << "搜索开始!\n\n";
#endif
			PuzzleState *node = astarsearch.GetSolutionStart();

			int steps = 0;

#if DISPLAY_SOLUTION_FORWARDS	// 显示前向步骤
			cout<<"初始状态："<<endl;
			node->PrintNodeInfo();	// 输出到终端
			cout<<endl;
			
			node->WriteNodeInfo();	// 输出到文件
			
#endif
			cout << "前向步骤：\n";
			// 搜索下一个节点
			for( ;; )
			{
				
				node = astarsearch.GetSolutionNext();

				if( !node )
				{
					break;
				}

#if DISPLAY_SOLUTION_FORWARDS	// 显示前向步骤
				node->PrintNodeInfo();
				cout << endl;
#endif
				steps ++;
			
			};

#if DISPLAY_SOLUTION_FORWARDS	// 显示后向步骤
			cout << "步数： " << steps << endl<<endl;
#endif

////////////
			cout<<"最终状态："<<endl;
			node = astarsearch.GetSolutionEnd();
			
			
			
			
#if DISPLAY_SOLUTION_BACKWARDS	// 显示后向步骤
			cout << "显示后向步骤：\n";
#endif
			steps = 0;

			node->PrintNodeInfo();
			cout << endl;
			for( ;; )
			{
				node = astarsearch.GetSolutionPrev();

				if( !node )
				{
					break;
				}
#if DISPLAY_SOLUTION_BACKWARDS	// 显示后向步骤
				node->PrintNodeInfo();
                cout << endl;
#endif
				steps ++;
			
			};

#if DISPLAY_SOLUTION_BACKWARDS	// 显示后向步骤
			cout << "步数： " << steps << endl;
#endif

//////////////

			// Once you're done with the solution you can free the nodes up
			astarsearch.FreeSolutionNodes();
		
		}
		else if( SearchState == AStarSearch<PuzzleState>::SEARCH_STATE_FAILED ) 
		{
#if DISPLAY_SOLUTION_INFO
			cout << "搜索终止！没有找到目标状态！\n";
#endif		
		}
		else if( SearchState == AStarSearch<PuzzleState>::SEARCH_STATE_OUT_OF_MEMORY ) 
		{
#if DISPLAY_SOLUTION_INFO
			cout << "搜索终止！内存耗尽！\n";
#endif		
		}

// Display the number of loops the search went through
// #if DISPLAY_SOLUTION_INFO
// 		cout << "搜索次数： " << astarsearch.GetStepCount() << endl;
// #endif

			// 加入终点
			Move.push_back(make_pair(2,2));
			
			int len_Move = Move.size();
			
			// 输出到文件
			ofstream out("24puzzle_move.txt");
			
			// 输出空白格运动路径
			for(int i=0; i<len_Move-3; i++)
			{
				int r1 = Move[i].first;
				int c1 = Move[i].second;
				int r2 = Move[i+1].first;
				int c2 = Move[i+1].second;
				
				// cout<<"第"<<i<<"次移动：("<<r1<<","<<c1<<") -> ("<<r2<<","<<c2<<")"<<endl;
				out<<r1<<" "<<c1<<" "<<r2<<" "<<c2<<endl;
			}
	}

	return 0;
}


