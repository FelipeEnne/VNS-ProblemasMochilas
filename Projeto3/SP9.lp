\ LP format - for model browsing. Use MPS format to capture full model detail.
Minimize
  0.25 x11 - 0.75 x21 - 0.75 x31 + x22 - 0.75 x13 - 0.75 x23 + 0.25 x33 + y1
   + y2 + y3 - 0.25 Constant
Subject To
 c1: x11 - y1 <= 0
 c2: x12 - y1 <= 0
 c3: x13 - y1 <= 0
 c4: x21 - y2 <= 0
 c5: x22 - y2 <= 0
 c6: x23 - y2 <= 0
 c7: x31 - y3 <= 0
 c8: x32 - y3 <= 0
 c9: x33 - y3 <= 0
Bounds
 x11 <= 1
 x21 <= 1
 x31 <= 1
 x12 <= 1
 x22 <= 1
 x32 <= 1
 x13 <= 1
 x23 <= 1
 x33 <= 1
 y1 <= 1
 y2 <= 1
 y3 <= 1
 Constant = 1
End
