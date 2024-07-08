// Function to detect the lane using Pixy2
int laneDetection() {
  pixy.ccc.getBlocks();
  
  if (pixy.ccc.numBlocks) {
    int x = pixy.ccc.blocks[0].m_x;
    return x;
  }
  
  return -1;
}
