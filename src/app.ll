; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind uwtable
define dso_local void @generateWorld(i8* nocapture noundef writeonly %0) local_unnamed_addr #0 {
  br label %2

2:                                                ; preds = %1, %7
  %3 = phi i64 [ 0, %1 ], [ %8, %7 ]
  %4 = mul nuw nsw i64 %3, 50
  %5 = getelementptr inbounds i8, i8* %0, i64 %4
  br label %10

6:                                                ; preds = %7
  ret void

7:                                                ; preds = %10
  %8 = add nuw nsw i64 %3, 1
  %9 = icmp eq i64 %8, 50
  br i1 %9, label %6, label %2, !llvm.loop !5

10:                                               ; preds = %2, %10
  %11 = phi i64 [ 0, %2 ], [ %16, %10 ]
  %12 = tail call i32 @rand() #6
  %13 = getelementptr inbounds i8, i8* %5, i64 %11
  %14 = trunc i32 %12 to i8
  %15 = and i8 %14, 1
  store i8 %15, i8* %13, align 1, !tbaa !7
  %16 = add nuw nsw i64 %11, 1
  %17 = icmp eq i64 %16, 50
  br i1 %17, label %7, label %10, !llvm.loop !11
}

; Function Attrs: nounwind
declare i32 @rand() local_unnamed_addr #1

; Function Attrs: mustprogress nofree norecurse nosync nounwind readonly uwtable willreturn
define dso_local i32 @toUint(i8* nocapture noundef readonly %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #2 {
  %4 = icmp ugt i32 %2, 49
  %5 = icmp ugt i32 %1, 49
  %6 = or i1 %5, %4
  br i1 %6, label %15, label %7

7:                                                ; preds = %3
  %8 = zext i32 %1 to i64
  %9 = mul nuw nsw i64 %8, 50
  %10 = getelementptr inbounds i8, i8* %0, i64 %9
  %11 = zext i32 %2 to i64
  %12 = getelementptr inbounds i8, i8* %10, i64 %11
  %13 = load i8, i8* %12, align 1, !tbaa !7, !range !12
  %14 = zext i8 %13 to i32
  br label %15

15:                                               ; preds = %3, %7
  %16 = phi i32 [ %14, %7 ], [ 0, %3 ]
  ret i32 %16
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind uwtable willreturn writeonly
define dso_local void @updateCell(i1 noundef zeroext %0, i8* nocapture noundef writeonly %1, i32 noundef %2) local_unnamed_addr #3 {
  %4 = and i32 %2, -2
  %5 = icmp eq i32 %4, 2
  %6 = icmp sgt i32 %2, 2
  %7 = select i1 %0, i1 %5, i1 %6
  %8 = zext i1 %7 to i8
  store i8 %8, i8* %1, align 1, !tbaa !7
  ret void
}

; Function Attrs: nofree norecurse nosync nounwind uwtable
define dso_local void @updateWorld(i8* nocapture noundef readonly %0, i8* nocapture noundef writeonly %1) local_unnamed_addr #4 {
  br label %3

3:                                                ; preds = %2, %19
  %4 = phi i64 [ 0, %2 ], [ %8, %19 ]
  %5 = trunc i64 %4 to i32
  %6 = add i32 %5, -1
  %7 = icmp ugt i32 %6, 49
  %8 = add nuw nsw i64 %4, 1
  %9 = icmp ugt i64 %4, 48
  %10 = mul nuw nsw i64 %4, 50
  %11 = getelementptr inbounds i8, i8* %0, i64 %10
  %12 = getelementptr inbounds i8, i8* %1, i64 %10
  %13 = zext i32 %6 to i64
  %14 = mul nuw nsw i64 %13, 50
  %15 = getelementptr inbounds i8, i8* %0, i64 %14
  %16 = mul nuw nsw i64 %8, 50
  %17 = getelementptr inbounds i8, i8* %0, i64 %16
  br label %21

18:                                               ; preds = %19
  ret void

19:                                               ; preds = %71
  %20 = icmp eq i64 %8, 50
  br i1 %20, label %18, label %3, !llvm.loop !13

21:                                               ; preds = %3, %71
  %22 = phi i64 [ 0, %3 ], [ %43, %71 ]
  %23 = trunc i64 %22 to i32
  %24 = add i32 %23, -1
  %25 = icmp ugt i32 %24, 49
  %26 = or i1 %7, %25
  br i1 %26, label %33, label %27

27:                                               ; preds = %21
  %28 = zext i32 %24 to i64
  %29 = getelementptr inbounds i8, i8* %15, i64 %28
  %30 = load i8, i8* %29, align 1, !tbaa !7, !range !12
  %31 = mul nuw nsw i8 %30, 3
  %32 = zext i8 %31 to i32
  br label %33

33:                                               ; preds = %21, %27
  %34 = phi i32 [ %32, %27 ], [ 0, %21 ]
  br i1 %25, label %40, label %35

35:                                               ; preds = %33
  %36 = zext i32 %24 to i64
  %37 = getelementptr inbounds i8, i8* %11, i64 %36
  %38 = load i8, i8* %37, align 1, !tbaa !7, !range !12
  %39 = zext i8 %38 to i32
  br label %40

40:                                               ; preds = %33, %35
  %41 = phi i32 [ %39, %35 ], [ 0, %33 ]
  %42 = add nuw nsw i32 %41, %34
  %43 = add nuw nsw i64 %22, 1
  %44 = icmp ugt i64 %22, 48
  br i1 %44, label %49, label %45

45:                                               ; preds = %40
  %46 = getelementptr inbounds i8, i8* %11, i64 %43
  %47 = load i8, i8* %46, align 1, !tbaa !7, !range !12
  %48 = zext i8 %47 to i32
  br label %49

49:                                               ; preds = %40, %45
  %50 = phi i32 [ %48, %45 ], [ 0, %40 ]
  %51 = add nuw nsw i32 %42, %50
  %52 = or i1 %9, %25
  br i1 %52, label %58, label %53

53:                                               ; preds = %49
  %54 = zext i32 %24 to i64
  %55 = getelementptr inbounds i8, i8* %17, i64 %54
  %56 = load i8, i8* %55, align 1, !tbaa !7, !range !12
  %57 = zext i8 %56 to i32
  br label %58

58:                                               ; preds = %49, %53
  %59 = phi i32 [ %57, %53 ], [ 0, %49 ]
  %60 = add nuw nsw i32 %51, %59
  br i1 %9, label %71, label %61

61:                                               ; preds = %58
  %62 = getelementptr inbounds i8, i8* %17, i64 %22
  %63 = load i8, i8* %62, align 1, !tbaa !7, !range !12
  %64 = zext i8 %63 to i32
  %65 = add nuw nsw i32 %60, %64
  %66 = or i1 %9, %44
  br i1 %66, label %71, label %67

67:                                               ; preds = %61
  %68 = getelementptr inbounds i8, i8* %17, i64 %43
  %69 = load i8, i8* %68, align 1, !tbaa !7, !range !12
  %70 = zext i8 %69 to i32
  br label %71

71:                                               ; preds = %58, %61, %67
  %72 = phi i32 [ %65, %67 ], [ %65, %61 ], [ %60, %58 ]
  %73 = phi i32 [ %70, %67 ], [ 0, %61 ], [ 0, %58 ]
  %74 = add nuw nsw i32 %72, %73
  %75 = getelementptr inbounds i8, i8* %11, i64 %22
  %76 = load i8, i8* %75, align 1, !tbaa !7, !range !12
  %77 = icmp eq i8 %76, 0
  %78 = getelementptr inbounds i8, i8* %12, i64 %22
  %79 = and i32 %74, -2
  %80 = icmp eq i32 %79, 2
  %81 = icmp ugt i32 %74, 2
  %82 = select i1 %77, i1 %81, i1 %80
  %83 = zext i1 %82 to i8
  store i8 %83, i8* %78, align 1, !tbaa !7
  %84 = icmp eq i64 %43, 50
  br i1 %84, label %19, label %21, !llvm.loop !14
}

; Function Attrs: nounwind uwtable
define dso_local void @app() local_unnamed_addr #0 {
  %1 = alloca [2500 x i8], align 16
  %2 = alloca [2500 x i8], align 16
  %3 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 0
  br label %4

4:                                                ; preds = %8, %0
  %5 = phi i64 [ 0, %0 ], [ %9, %8 ]
  %6 = mul nuw nsw i64 %5, 50
  %7 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %6
  br label %11

8:                                                ; preds = %11
  %9 = add nuw nsw i64 %5, 1
  %10 = icmp eq i64 %9, 50
  br i1 %10, label %19, label %4, !llvm.loop !5

11:                                               ; preds = %11, %4
  %12 = phi i64 [ 0, %4 ], [ %17, %11 ]
  %13 = tail call i32 @rand() #6
  %14 = getelementptr inbounds i8, i8* %7, i64 %12
  %15 = trunc i32 %13 to i8
  %16 = and i8 %15, 1
  store i8 %16, i8* %14, align 1, !tbaa !7
  %17 = add nuw nsw i64 %12, 1
  %18 = icmp eq i64 %17, 50
  br i1 %18, label %8, label %11, !llvm.loop !11

19:                                               ; preds = %8
  %20 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 0
  call void @drawWorld(i8* noundef nonnull %20) #6
  br label %21

21:                                               ; preds = %38, %19
  %22 = phi i64 [ 0, %19 ], [ %39, %38 ]
  %23 = trunc i64 %22 to i32
  %24 = add i32 %23, -1
  %25 = icmp ugt i32 %24, 49
  %26 = add nuw nsw i64 %22, 1
  %27 = icmp ugt i64 %22, 48
  %28 = mul nuw nsw i64 %22, 50
  %29 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %28
  %30 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 %28
  %31 = zext i32 %24 to i64
  %32 = mul nuw nsw i64 %31, 50
  %33 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %32
  %34 = mul nuw nsw i64 %26, 50
  %35 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %34
  br label %40

36:                                               ; preds = %89
  %37 = icmp eq i64 %26, 50
  br i1 %37, label %103, label %38

38:                                               ; preds = %36, %235
  %39 = phi i64 [ %26, %36 ], [ 0, %235 ]
  br label %21, !llvm.loop !13

40:                                               ; preds = %89, %21
  %41 = phi i64 [ 0, %21 ], [ %62, %89 ]
  %42 = trunc i64 %41 to i32
  %43 = add i32 %42, -1
  %44 = icmp ugt i32 %43, 49
  %45 = or i1 %25, %44
  br i1 %45, label %52, label %46

46:                                               ; preds = %40
  %47 = zext i32 %43 to i64
  %48 = getelementptr inbounds i8, i8* %33, i64 %47
  %49 = load i8, i8* %48, align 1, !tbaa !7, !range !12
  %50 = mul nuw nsw i8 %49, 3
  %51 = zext i8 %50 to i32
  br label %52

52:                                               ; preds = %46, %40
  %53 = phi i32 [ %51, %46 ], [ 0, %40 ]
  br i1 %44, label %59, label %54

54:                                               ; preds = %52
  %55 = zext i32 %43 to i64
  %56 = getelementptr inbounds i8, i8* %29, i64 %55
  %57 = load i8, i8* %56, align 1, !tbaa !7, !range !12
  %58 = zext i8 %57 to i32
  br label %59

59:                                               ; preds = %54, %52
  %60 = phi i32 [ %58, %54 ], [ 0, %52 ]
  %61 = add nuw nsw i32 %60, %53
  %62 = add nuw nsw i64 %41, 1
  %63 = icmp ugt i64 %41, 48
  br i1 %63, label %68, label %64

64:                                               ; preds = %59
  %65 = getelementptr inbounds i8, i8* %29, i64 %62
  %66 = load i8, i8* %65, align 1, !tbaa !7, !range !12
  %67 = zext i8 %66 to i32
  br label %68

68:                                               ; preds = %64, %59
  %69 = phi i32 [ %67, %64 ], [ 0, %59 ]
  %70 = add nuw nsw i32 %61, %69
  %71 = or i1 %27, %44
  br i1 %71, label %77, label %72

72:                                               ; preds = %68
  %73 = zext i32 %43 to i64
  %74 = getelementptr inbounds i8, i8* %35, i64 %73
  %75 = load i8, i8* %74, align 1, !tbaa !7, !range !12
  %76 = zext i8 %75 to i32
  br label %77

77:                                               ; preds = %72, %68
  %78 = phi i32 [ %76, %72 ], [ 0, %68 ]
  %79 = add nuw nsw i32 %70, %78
  br i1 %27, label %89, label %80

80:                                               ; preds = %77
  %81 = getelementptr inbounds i8, i8* %35, i64 %41
  %82 = load i8, i8* %81, align 1, !tbaa !7, !range !12
  %83 = zext i8 %82 to i32
  %84 = add nuw nsw i32 %79, %83
  br i1 %63, label %89, label %85

85:                                               ; preds = %80
  %86 = getelementptr inbounds i8, i8* %35, i64 %62
  %87 = load i8, i8* %86, align 1, !tbaa !7, !range !12
  %88 = zext i8 %87 to i32
  br label %89

89:                                               ; preds = %85, %80, %77
  %90 = phi i32 [ %84, %85 ], [ %84, %80 ], [ %79, %77 ]
  %91 = phi i32 [ %88, %85 ], [ 0, %80 ], [ 0, %77 ]
  %92 = add nuw nsw i32 %91, %90
  %93 = getelementptr inbounds i8, i8* %29, i64 %41
  %94 = load i8, i8* %93, align 1, !tbaa !7, !range !12
  %95 = icmp eq i8 %94, 0
  %96 = getelementptr inbounds i8, i8* %30, i64 %41
  %97 = and i32 %92, -2
  %98 = icmp eq i32 %97, 2
  %99 = icmp ugt i32 %92, 2
  %100 = select i1 %95, i1 %99, i1 %98
  %101 = zext i1 %100 to i8
  store i8 %101, i8* %96, align 1, !tbaa !7
  %102 = icmp eq i64 %62, 50
  br i1 %102, label %36, label %40, !llvm.loop !14

103:                                              ; preds = %36
  call void @drawWorld(i8* noundef nonnull %3) #6
  br label %104

104:                                              ; preds = %119, %103
  %105 = phi i64 [ 0, %103 ], [ %109, %119 ]
  %106 = trunc i64 %105 to i32
  %107 = add i32 %106, -1
  %108 = icmp ugt i32 %107, 49
  %109 = add nuw nsw i64 %105, 1
  %110 = icmp ugt i64 %105, 48
  %111 = mul nuw nsw i64 %105, 50
  %112 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 %111
  %113 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %111
  %114 = zext i32 %107 to i64
  %115 = mul nuw nsw i64 %114, 50
  %116 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 %115
  %117 = mul nuw nsw i64 %109, 50
  %118 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 %117
  br label %121

119:                                              ; preds = %170
  %120 = icmp eq i64 %109, 50
  br i1 %120, label %184, label %104, !llvm.loop !13

121:                                              ; preds = %170, %104
  %122 = phi i64 [ 0, %104 ], [ %143, %170 ]
  %123 = trunc i64 %122 to i32
  %124 = add i32 %123, -1
  %125 = icmp ugt i32 %124, 49
  %126 = or i1 %108, %125
  br i1 %126, label %133, label %127

127:                                              ; preds = %121
  %128 = zext i32 %124 to i64
  %129 = getelementptr inbounds i8, i8* %116, i64 %128
  %130 = load i8, i8* %129, align 1, !tbaa !7, !range !12
  %131 = mul nuw nsw i8 %130, 3
  %132 = zext i8 %131 to i32
  br label %133

133:                                              ; preds = %127, %121
  %134 = phi i32 [ %132, %127 ], [ 0, %121 ]
  br i1 %125, label %140, label %135

135:                                              ; preds = %133
  %136 = zext i32 %124 to i64
  %137 = getelementptr inbounds i8, i8* %112, i64 %136
  %138 = load i8, i8* %137, align 1, !tbaa !7, !range !12
  %139 = zext i8 %138 to i32
  br label %140

140:                                              ; preds = %135, %133
  %141 = phi i32 [ %139, %135 ], [ 0, %133 ]
  %142 = add nuw nsw i32 %141, %134
  %143 = add nuw nsw i64 %122, 1
  %144 = icmp ugt i64 %122, 48
  br i1 %144, label %149, label %145

145:                                              ; preds = %140
  %146 = getelementptr inbounds i8, i8* %112, i64 %143
  %147 = load i8, i8* %146, align 1, !tbaa !7, !range !12
  %148 = zext i8 %147 to i32
  br label %149

149:                                              ; preds = %145, %140
  %150 = phi i32 [ %148, %145 ], [ 0, %140 ]
  %151 = add nuw nsw i32 %142, %150
  %152 = or i1 %110, %125
  br i1 %152, label %158, label %153

153:                                              ; preds = %149
  %154 = zext i32 %124 to i64
  %155 = getelementptr inbounds i8, i8* %118, i64 %154
  %156 = load i8, i8* %155, align 1, !tbaa !7, !range !12
  %157 = zext i8 %156 to i32
  br label %158

158:                                              ; preds = %153, %149
  %159 = phi i32 [ %157, %153 ], [ 0, %149 ]
  %160 = add nuw nsw i32 %151, %159
  br i1 %110, label %170, label %161

161:                                              ; preds = %158
  %162 = getelementptr inbounds i8, i8* %118, i64 %122
  %163 = load i8, i8* %162, align 1, !tbaa !7, !range !12
  %164 = zext i8 %163 to i32
  %165 = add nuw nsw i32 %160, %164
  br i1 %144, label %170, label %166

166:                                              ; preds = %161
  %167 = getelementptr inbounds i8, i8* %118, i64 %143
  %168 = load i8, i8* %167, align 1, !tbaa !7, !range !12
  %169 = zext i8 %168 to i32
  br label %170

170:                                              ; preds = %166, %161, %158
  %171 = phi i32 [ %165, %166 ], [ %165, %161 ], [ %160, %158 ]
  %172 = phi i32 [ %169, %166 ], [ 0, %161 ], [ 0, %158 ]
  %173 = add nuw nsw i32 %172, %171
  %174 = getelementptr inbounds i8, i8* %112, i64 %122
  %175 = load i8, i8* %174, align 1, !tbaa !7, !range !12
  %176 = icmp eq i8 %175, 0
  %177 = getelementptr inbounds i8, i8* %113, i64 %122
  %178 = and i32 %173, -2
  %179 = icmp eq i32 %178, 2
  %180 = icmp ugt i32 %173, 2
  %181 = select i1 %176, i1 %180, i1 %179
  %182 = zext i1 %181 to i8
  store i8 %182, i8* %177, align 1, !tbaa !7
  %183 = icmp eq i64 %143, 50
  br i1 %183, label %119, label %121, !llvm.loop !14

184:                                              ; preds = %119
  call void @drawWorld(i8* noundef nonnull %20) #6
  br label %185

185:                                              ; preds = %184, %185
  %186 = phi i64 [ 0, %184 ], [ %233, %185 ]
  %187 = phi i8 [ 1, %184 ], [ %232, %185 ]
  %188 = mul nuw nsw i64 %186, 50
  %189 = getelementptr inbounds [2500 x i8], [2500 x i8]* %1, i64 0, i64 %188
  %190 = getelementptr inbounds [2500 x i8], [2500 x i8]* %2, i64 0, i64 %188
  %191 = getelementptr inbounds i8, i8* %189, i64 32
  %192 = bitcast i8* %191 to <16 x i8>*
  %193 = load <16 x i8>, <16 x i8>* %192, align 2, !tbaa !7
  %194 = getelementptr inbounds i8, i8* %190, i64 32
  %195 = bitcast i8* %194 to <16 x i8>*
  %196 = load <16 x i8>, <16 x i8>* %195, align 2, !tbaa !7
  %197 = icmp eq <16 x i8> %193, %196
  %198 = getelementptr inbounds i8, i8* %189, i64 16
  %199 = bitcast i8* %198 to <16 x i8>*
  %200 = load <16 x i8>, <16 x i8>* %199, align 2, !tbaa !7
  %201 = getelementptr inbounds i8, i8* %190, i64 16
  %202 = bitcast i8* %201 to <16 x i8>*
  %203 = load <16 x i8>, <16 x i8>* %202, align 2, !tbaa !7
  %204 = icmp eq <16 x i8> %200, %203
  %205 = select <16 x i1> %197, <16 x i1> %204, <16 x i1> zeroinitializer
  %206 = bitcast i8* %189 to <16 x i8>*
  %207 = load <16 x i8>, <16 x i8>* %206, align 2, !tbaa !7
  %208 = bitcast i8* %190 to <16 x i8>*
  %209 = load <16 x i8>, <16 x i8>* %208, align 2, !tbaa !7
  %210 = icmp eq <16 x i8> %207, %209
  %211 = select <16 x i1> %205, <16 x i1> %210, <16 x i1> zeroinitializer
  %212 = insertelement <16 x i8> poison, i8 %187, i64 0
  %213 = shufflevector <16 x i8> %212, <16 x i8> poison, <16 x i32> zeroinitializer
  %214 = select <16 x i1> %211, <16 x i8> %213, <16 x i8> zeroinitializer
  %215 = insertelement <16 x i8> poison, i8 %187, i64 0
  %216 = shufflevector <16 x i8> %215, <16 x i8> poison, <16 x i32> zeroinitializer
  %217 = icmp ne <16 x i8> %214, %216
  %218 = bitcast <16 x i1> %217 to i16
  %219 = icmp eq i16 %218, 0
  %220 = getelementptr inbounds i8, i8* %189, i64 48
  %221 = load i8, i8* %220, align 2, !tbaa !7, !range !12
  %222 = getelementptr inbounds i8, i8* %190, i64 48
  %223 = load i8, i8* %222, align 2, !tbaa !7, !range !12
  %224 = icmp eq i8 %221, %223
  %225 = getelementptr inbounds i8, i8* %189, i64 49
  %226 = load i8, i8* %225, align 1, !tbaa !7, !range !12
  %227 = getelementptr inbounds i8, i8* %190, i64 49
  %228 = load i8, i8* %227, align 1, !tbaa !7, !range !12
  %229 = icmp eq i8 %226, %228
  %230 = select i1 %229, i1 %224, i1 false
  %231 = select i1 %230, i1 %219, i1 false
  %232 = select i1 %231, i8 %187, i8 0
  %233 = add nuw nsw i64 %186, 1
  %234 = icmp eq i64 %233, 50
  br i1 %234, label %235, label %185, !llvm.loop !15

235:                                              ; preds = %185
  %236 = and i8 %232, 1
  %237 = icmp eq i8 %236, 0
  br i1 %237, label %38, label %238

238:                                              ; preds = %235
  ret void
}

declare void @drawWorld(i8* noundef) local_unnamed_addr #5

attributes #0 = { nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress nofree norecurse nosync nounwind readonly uwtable willreturn "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nofree norecurse nosync nounwind uwtable willreturn writeonly "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nofree norecurse nosync nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.mustprogress"}
!7 = !{!8, !8, i64 0}
!8 = !{!"_Bool", !9, i64 0}
!9 = !{!"omnipotent char", !10, i64 0}
!10 = !{!"Simple C/C++ TBAA"}
!11 = distinct !{!11, !6}
!12 = !{i8 0, i8 2}
!13 = distinct !{!13, !6}
!14 = distinct !{!14, !6}
!15 = distinct !{!15, !6}
