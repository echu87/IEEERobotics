int path[28][2];
int counter = 1;
int visited[28][2];
int visitedCounter = 0;
int obstruct[58][4];
int obstructCounter = 0;

void setup() {
  Serial.begin(9600);

  addObstruction(0,0,0,1);
  addObstruction(1,0,2,0);
  addObstruction(2,2,3,2);
  addObstruction(2,2,2,3);
  addObstruction(3,1,3,2);
  addObstruction(1,2,1,3);
  addObstruction(0,4,0,5);
  addObstruction(1,4,2,4);
  addObstruction(1,5,2,5);
  addObstruction(3,5,3,6);
  
  s(0,0);
  for (int i = 0; i < counter; i++) {
    Serial.print(path[i][0]);
    Serial.print(',');
    Serial.println(path[i][1]);
  }
}

void loop() {

}

void s(int x, int y) {
  path[0][0] = x;
  path[0][1] = y;
  counter = 1;
  search();
}

void search() {
  int pos[2];
  pos[0] = path[0][0];
  pos[1] = path[0][1];
  int skip = false;
  while (!skip) {
    visitedCounter = visitedCounter + 1;
    visited[visitedCounter][0] = pos[0];
    visited[visitedCounter][1] = pos[1];
    
    int adjacent[4][2] = {{pos[0],pos[1]},{pos[0],pos[1]},{pos[0],pos[1]},{pos[0],pos[1]}};
    neighbours(adjacent);
    int nextPos[2];
    float closest = 999;
    for (int i = 0; i < 4; i++) {
      bool obstructed = false;
      for (int j = 0; j < obstructCounter; j++) {
        if (obstruct[j][0] == pos[0] && obstruct[j][1] == pos[1] && obstruct[j][2] == adjacent[i][0] && obstruct[j][3] == adjacent[i][1])
          obstructed = true;
        if (obstruct[j][2] == pos[0] && obstruct[j][3] == pos[1] && obstruct[j][0] == adjacent[i][0] && obstruct[j][1] == adjacent[i][1])
          obstructed = true;
      }
      if (obstructed)
        continue;
      if (adjacent[i][0] != 999 ) {
        float h = heuristic(adjacent[i]);
        bool incl = false;
        for (int j = 0; j < visitedCounter; j++)
          if (visited[j][0] == adjacent[i][0] && visited[j][1] == adjacent[i][1])
            incl = true;
        if (incl)
          h = h + .1;
        if (h < closest) {
          closest = h;
          nextPos[0] = adjacent[i][0];
          nextPos[1] = adjacent[i][1];
        }
      }
    }
    
    if (path[counter-2][0] == nextPos[0] && path[counter-2][1] == nextPos[1])
      addObstruction(pos[0], pos[1], nextPos[0], nextPos[1]);
    
    pos[0] = nextPos[0];
    pos[1] = nextPos[1];  
    if (!(path[counter-2][0] == nextPos[0] && path[counter-2][1] == nextPos[1]) || counter == 0 || counter == 1) {
      path[counter][0] = pos[0];
      path[counter][1] = pos[1];
      counter = counter + 1; 
    } else {
      counter = counter - 1;
    }

    // addObstruction(pos[1], pos[2], path[counter][0], path[counter][1]);
    if (pos[0] == 3 && pos[1] == 6)
      skip = true;
  }
}

void addObstruction(int sx, int sy, int fx, int fy) {
  obstruct[obstructCounter][0] = sx;
  obstruct[obstructCounter][1] = sy;
  obstruct[obstructCounter][2] = fx;
  obstruct[obstructCounter][3] = fy;
  obstructCounter = obstructCounter + 1;
}

float heuristic(int pos[2]) {
  return (3 - pos[0]) + (6 - pos[1]);
}

void neighbours(int pos[4][2]) {
  int coords[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
  for (int i = 0; i < 4; i++) {
    int x = pos[i][0] + coords[i][0];
    int y = pos[i][1] + coords[i][1];
    if (x >= 0 && x <= 3 && y >= 0 && y <= 6) {
      pos[i][0] = x;
      pos[i][1] = y; 
    } else {
      pos[i][0] = 999;
      pos[i][1] = 999;
    }
  }
}
