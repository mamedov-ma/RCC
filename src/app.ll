; ModuleID = 'app.cpp'
source_filename = "app.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"class.std::ios_base::Init" = type { i8 }
%struct.SDL_Renderer = type opaque
%struct.SDL_Rect = type { i32, i32, i32, i32 }
%struct.SDL_Window = type opaque

@_ZStL8__ioinit = internal global %"class.std::ios_base::Init" zeroinitializer, align 1
@__dso_handle = external hidden global i8
@WORLD_SIZE = dso_local local_unnamed_addr global i32 500, align 4
@renderer = dso_local local_unnamed_addr global %struct.SDL_Renderer* null, align 8
@.str = private unnamed_addr constant [13 x i8] c"Game Of Life\00", align 1
@llvm.global_ctors = appending global [1 x { i32, void ()*, i8* }] [{ i32, void ()*, i8* } { i32 65535, void ()* @_GLOBAL__sub_I_app.cpp, i8* null }]

declare void @_ZNSt8ios_base4InitC1Ev(%"class.std::ios_base::Init"* noundef nonnull align 1 dereferenceable(1)) unnamed_addr #0

; Function Attrs: nounwind
declare void @_ZNSt8ios_base4InitD1Ev(%"class.std::ios_base::Init"* noundef nonnull align 1 dereferenceable(1)) unnamed_addr #1

; Function Attrs: nofree nounwind
declare i32 @__cxa_atexit(void (i8*)*, i8*, i8*) local_unnamed_addr #2

; Function Attrs: mustprogress uwtable
define dso_local void @_Z9drawWorldPPb(i8** nocapture noundef readonly %0) local_unnamed_addr #3 {
  %2 = alloca %struct.SDL_Rect, align 4
  %3 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @renderer, align 8, !tbaa !5
  %4 = tail call i32 @SDL_SetRenderDrawColor(%struct.SDL_Renderer* noundef %3, i8 noundef zeroext 0, i8 noundef zeroext 0, i8 noundef zeroext 0, i8 noundef zeroext -1)
  %5 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @renderer, align 8, !tbaa !5
  %6 = tail call i32 @SDL_RenderClear(%struct.SDL_Renderer* noundef %5)
  %7 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @renderer, align 8, !tbaa !5
  %8 = tail call i32 @SDL_SetRenderDrawColor(%struct.SDL_Renderer* noundef %7, i8 noundef zeroext -1, i8 noundef zeroext -1, i8 noundef zeroext -1, i8 noundef zeroext -1)
  %9 = load i32, i32* @WORLD_SIZE, align 4, !tbaa !9
  %10 = icmp sgt i32 %9, 0
  br i1 %10, label %11, label %24

11:                                               ; preds = %1
  %12 = bitcast %struct.SDL_Rect* %2 to i8*
  %13 = getelementptr inbounds %struct.SDL_Rect, %struct.SDL_Rect* %2, i64 0, i32 0
  %14 = getelementptr inbounds %struct.SDL_Rect, %struct.SDL_Rect* %2, i64 0, i32 1
  %15 = getelementptr inbounds %struct.SDL_Rect, %struct.SDL_Rect* %2, i64 0, i32 2
  %16 = getelementptr inbounds %struct.SDL_Rect, %struct.SDL_Rect* %2, i64 0, i32 3
  br label %17

17:                                               ; preds = %11, %26
  %18 = phi i32 [ %9, %11 ], [ %27, %26 ]
  %19 = phi i64 [ 0, %11 ], [ %28, %26 ]
  %20 = icmp sgt i32 %18, 0
  br i1 %20, label %21, label %26

21:                                               ; preds = %17
  %22 = getelementptr inbounds i8*, i8** %0, i64 %19
  %23 = trunc i64 %19 to i32
  br label %31

24:                                               ; preds = %26, %1
  %25 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @renderer, align 8, !tbaa !5
  call void @SDL_RenderPresent(%struct.SDL_Renderer* noundef %25)
  ret void

26:                                               ; preds = %44, %17
  %27 = phi i32 [ %18, %17 ], [ %45, %44 ]
  %28 = add nuw nsw i64 %19, 1
  %29 = sext i32 %27 to i64
  %30 = icmp slt i64 %28, %29
  br i1 %30, label %17, label %24, !llvm.loop !11

31:                                               ; preds = %21, %44
  %32 = phi i32 [ %18, %21 ], [ %45, %44 ]
  %33 = phi i32 [ %18, %21 ], [ %46, %44 ]
  %34 = phi i64 [ 0, %21 ], [ %47, %44 ]
  %35 = load i8*, i8** %22, align 8, !tbaa !5
  %36 = getelementptr inbounds i8, i8* %35, i64 %34
  %37 = load i8, i8* %36, align 1, !tbaa !13, !range !15
  %38 = icmp eq i8 %37, 0
  br i1 %38, label %44, label %39

39:                                               ; preds = %31
  call void @llvm.lifetime.start.p0i8(i64 16, i8* nonnull %12) #12
  %40 = trunc i64 %34 to i32
  store i32 %40, i32* %13, align 4, !tbaa !16
  store i32 %23, i32* %14, align 4, !tbaa !18
  store i32 1, i32* %15, align 4, !tbaa !19
  store i32 1, i32* %16, align 4, !tbaa !20
  %41 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @renderer, align 8, !tbaa !5
  %42 = call i32 @SDL_RenderFillRect(%struct.SDL_Renderer* noundef %41, %struct.SDL_Rect* noundef nonnull %2)
  call void @llvm.lifetime.end.p0i8(i64 16, i8* nonnull %12) #12
  %43 = load i32, i32* @WORLD_SIZE, align 4, !tbaa !9
  br label %44

44:                                               ; preds = %31, %39
  %45 = phi i32 [ %32, %31 ], [ %43, %39 ]
  %46 = phi i32 [ %33, %31 ], [ %43, %39 ]
  %47 = add nuw nsw i64 %34, 1
  %48 = sext i32 %46 to i64
  %49 = icmp slt i64 %47, %48
  br i1 %49, label %31, label %26, !llvm.loop !21
}

declare i32 @SDL_SetRenderDrawColor(%struct.SDL_Renderer* noundef, i8 noundef zeroext, i8 noundef zeroext, i8 noundef zeroext, i8 noundef zeroext) local_unnamed_addr #0

declare i32 @SDL_RenderClear(%struct.SDL_Renderer* noundef) local_unnamed_addr #0

; Function Attrs: argmemonly mustprogress nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #4

declare i32 @SDL_RenderFillRect(%struct.SDL_Renderer* noundef, %struct.SDL_Rect* noundef) local_unnamed_addr #0

; Function Attrs: argmemonly mustprogress nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #4

declare void @SDL_RenderPresent(%struct.SDL_Renderer* noundef) local_unnamed_addr #0

; Function Attrs: mustprogress uwtable
define dso_local noundef %struct.SDL_Renderer* @_Z14createRendererv() local_unnamed_addr #3 {
  %1 = tail call i32 @SDL_Init(i32 noundef 32)
  %2 = icmp eq i32 %1, 0
  br i1 %2, label %4, label %3

3:                                                ; preds = %0
  tail call void @exit(i32 noundef 1) #13
  unreachable

4:                                                ; preds = %0
  %5 = load i32, i32* @WORLD_SIZE, align 4, !tbaa !9
  %6 = tail call %struct.SDL_Window* @SDL_CreateWindow(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str, i64 0, i64 0), i32 noundef 805240832, i32 noundef 805240832, i32 noundef %5, i32 noundef %5, i32 noundef 4)
  %7 = icmp eq %struct.SDL_Window* %6, null
  br i1 %7, label %8, label %9

8:                                                ; preds = %4
  tail call void @exit(i32 noundef 1) #13
  unreachable

9:                                                ; preds = %4
  %10 = tail call %struct.SDL_Renderer* @SDL_CreateRenderer(%struct.SDL_Window* noundef nonnull %6, i32 noundef -1, i32 noundef 6)
  %11 = icmp eq %struct.SDL_Renderer* %10, null
  br i1 %11, label %12, label %13

12:                                               ; preds = %9
  tail call void @exit(i32 noundef 1) #13
  unreachable

13:                                               ; preds = %9
  ret %struct.SDL_Renderer* %10
}

declare i32 @SDL_Init(i32 noundef) local_unnamed_addr #0

; Function Attrs: noreturn nounwind
declare void @exit(i32 noundef) local_unnamed_addr #5

declare %struct.SDL_Window* @SDL_CreateWindow(i8* noundef, i32 noundef, i32 noundef, i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #0

declare %struct.SDL_Renderer* @SDL_CreateRenderer(%struct.SDL_Window* noundef, i32 noundef, i32 noundef) local_unnamed_addr #0

; Function Attrs: mustprogress uwtable
define dso_local void @_Z11stopDrawingv() local_unnamed_addr #3 {
  tail call void @SDL_Quit()
  ret void
}

declare void @SDL_Quit() local_unnamed_addr #0

; Function Attrs: mustprogress nounwind uwtable
define dso_local void @_Z13generateWorldPPb(i8** nocapture noundef readonly %0) local_unnamed_addr #6 {
  %2 = load i32, i32* @WORLD_SIZE, align 4, !tbaa !9
  %3 = icmp sgt i32 %2, 0
  br i1 %3, label %4, label %10

4:                                                ; preds = %1, %11
  %5 = phi i32 [ %12, %11 ], [ %2, %1 ]
  %6 = phi i64 [ %14, %11 ], [ 0, %1 ]
  %7 = icmp sgt i32 %5, 0
  br i1 %7, label %8, label %11

8:                                                ; preds = %4
  %9 = getelementptr inbounds i8*, i8** %0, i64 %6
  br label %16

10:                                               ; preds = %11, %1
  ret void

11:                                               ; preds = %16, %4
  %12 = phi i32 [ %5, %4 ], [ %24, %16 ]
  %13 = sext i32 %12 to i64
  %14 = add nuw nsw i64 %6, 1
  %15 = icmp slt i64 %14, %13
  br i1 %15, label %4, label %10, !llvm.loop !22

16:                                               ; preds = %8, %16
  %17 = phi i64 [ 0, %8 ], [ %23, %16 ]
  %18 = tail call i32 @rand() #12
  %19 = load i8*, i8** %9, align 8, !tbaa !5
  %20 = getelementptr inbounds i8, i8* %19, i64 %17
  %21 = trunc i32 %18 to i8
  %22 = and i8 %21, 1
  store i8 %22, i8* %20, align 1, !tbaa !13
  %23 = add nuw nsw i64 %17, 1
  %24 = load i32, i32* @WORLD_SIZE, align 4, !tbaa !9
  %25 = sext i32 %24 to i64
  %26 = icmp slt i64 %23, %25
  br i1 %26, label %16, label %11, !llvm.loop !23
}

; Function Attrs: nounwind
declare i32 @rand() local_unnamed_addr #1

; Function Attrs: mustprogress nofree norecurse nosync nounwind readonly uwtable willreturn
define dso_local noundef zeroext i8 @_Z6toUintPPbii(i8** nocapture noundef readonly %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #7 {
  %4 = load i32, i32* @WORLD_SIZE, align 4, !tbaa !9
  %5 = icmp sle i32 %4, %2
  %6 = icmp slt i32 %2, 0
  %7 = or i1 %6, %5
  br i1 %7, label %19, label %8

8:                                                ; preds = %3
  %9 = icmp sle i32 %4, %1
  %10 = icmp slt i32 %1, 0
  %11 = or i1 %10, %9
  br i1 %11, label %19, label %12

12:                                               ; preds = %8
  %13 = zext i32 %1 to i64
  %14 = getelementptr inbounds i8*, i8** %0, i64 %13
  %15 = load i8*, i8** %14, align 8, !tbaa !5
  %16 = zext i32 %2 to i64
  %17 = getelementptr inbounds i8, i8* %15, i64 %16
  %18 = load i8, i8* %17, align 1, !tbaa !13, !range !15
  br label %19

19:                                               ; preds = %3, %8, %12
  %20 = phi i8 [ %18, %12 ], [ 0, %8 ], [ 0, %3 ]
  ret i8 %20
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind uwtable willreturn writeonly
define dso_local void @_Z10updateCellbPbh(i1 noundef zeroext %0, i8* nocapture noundef writeonly %1, i8 noundef zeroext %2) local_unnamed_addr #8 {
  %4 = icmp ugt i8 %2, 2
  %5 = and i8 %2, -2
  %6 = icmp eq i8 %5, 2
  %7 = select i1 %0, i1 %6, i1 %4
  %8 = zext i1 %7 to i8
  store i8 %8, i8* %1, align 1, !tbaa !13
  ret void
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind uwtable
define dso_local void @_Z11updateWorldPPbS0_(i8** nocapture noundef readonly %0, i8** nocapture noundef readonly %1) local_unnamed_addr #9 {
  %3 = load i32, i32* @WORLD_SIZE, align 4, !tbaa !9
  %4 = icmp sgt i32 %3, 0
  br i1 %4, label %5, label %48

5:                                                ; preds = %2
  %6 = zext i32 %3 to i64
  %7 = zext i32 %3 to i64
  %8 = icmp eq i32 %3, 1
  %9 = icmp eq i32 %3, 1
  br label %10

10:                                               ; preds = %5, %49
  %11 = phi i64 [ 0, %5 ], [ %17, %49 ]
  %12 = icmp eq i64 %11, 0
  %13 = add nuw i64 %11, 4294967295
  %14 = and i64 %13, 4294967295
  %15 = getelementptr inbounds i8*, i8** %0, i64 %14
  %16 = getelementptr inbounds i8*, i8** %0, i64 %11
  %17 = add nuw nsw i64 %11, 1
  %18 = icmp uge i64 %17, %6
  %19 = getelementptr inbounds i8*, i8** %0, i64 %17
  %20 = load i8*, i8** %16, align 8, !tbaa !5
  %21 = getelementptr inbounds i8*, i8** %1, i64 %11
  %22 = load i8*, i8** %21, align 8, !tbaa !5
  br i1 %8, label %26, label %23

23:                                               ; preds = %10
  %24 = getelementptr inbounds i8, i8* %20, i64 1
  %25 = load i8, i8* %24, align 1, !tbaa !13, !range !15
  br label %26

26:                                               ; preds = %10, %23
  %27 = phi i8 [ %25, %23 ], [ 0, %10 ]
  br i1 %18, label %37, label %28

28:                                               ; preds = %26
  %29 = load i8*, i8** %19, align 8, !tbaa !5
  %30 = load i8, i8* %29, align 1, !tbaa !13, !range !15
  %31 = add nuw nsw i8 %27, %30
  %32 = select i1 %8, i1 true, i1 %18
  br i1 %32, label %37, label %33

33:                                               ; preds = %28
  %34 = load i8*, i8** %19, align 8, !tbaa !5
  %35 = getelementptr inbounds i8, i8* %34, i64 1
  %36 = load i8, i8* %35, align 1, !tbaa !13, !range !15
  br label %37

37:                                               ; preds = %26, %33, %28
  %38 = phi i8 [ %31, %33 ], [ %31, %28 ], [ %27, %26 ]
  %39 = phi i8 [ %36, %33 ], [ 0, %28 ], [ 0, %26 ]
  %40 = add nuw nsw i8 %38, %39
  %41 = load i8, i8* %20, align 1, !tbaa !13, !range !15
  %42 = icmp eq i8 %41, 0
  %43 = icmp ugt i8 %40, 2
  %44 = and i8 %40, 6
  %45 = icmp eq i8 %44, 2
  %46 = select i1 %42, i1 %43, i1 %45
  %47 = zext i1 %46 to i8
  store i8 %47, i8* %22, align 1, !tbaa !13
  br i1 %9, label %49, label %51

48:                                               ; preds = %49, %2
  ret void

49:                                               ; preds = %96, %37
  %50 = icmp eq i64 %17, %7
  br i1 %50, label %48, label %10, !llvm.loop !24

51:                                               ; preds = %37, %96
  %52 = phi i64 [ %74, %96 ], [ 1, %37 ]
  %53 = add nsw i64 %52, -1
  br i1 %12, label %68, label %54

54:                                               ; preds = %51
  %55 = load i8*, i8** %15, align 8, !tbaa !5
  %56 = and i64 %53, 4294967295
  %57 = getelementptr inbounds i8, i8* %55, i64 %56
  %58 = load i8, i8* %57, align 1, !tbaa !13, !range !15
  %59 = and i64 %53, 4294967295
  %60 = getelementptr inbounds i8, i8* %55, i64 %59
  %61 = load i8, i8* %60, align 1, !tbaa !13, !range !15
  %62 = add nuw nsw i8 %61, %58
  %63 = load i8*, i8** %15, align 8, !tbaa !5
  %64 = and i64 %53, 4294967295
  %65 = getelementptr inbounds i8, i8* %63, i64 %64
  %66 = load i8, i8* %65, align 1, !tbaa !13, !range !15
  %67 = add nuw nsw i8 %62, %66
  br label %68

68:                                               ; preds = %51, %54
  %69 = phi i8 [ %67, %54 ], [ 0, %51 ]
  %70 = and i64 %53, 4294967295
  %71 = getelementptr inbounds i8, i8* %20, i64 %70
  %72 = load i8, i8* %71, align 1, !tbaa !13, !range !15
  %73 = add nuw nsw i8 %72, %69
  %74 = add nuw nsw i64 %52, 1
  %75 = icmp uge i64 %74, %6
  br i1 %75, label %79, label %76

76:                                               ; preds = %68
  %77 = getelementptr inbounds i8, i8* %20, i64 %74
  %78 = load i8, i8* %77, align 1, !tbaa !13, !range !15
  br label %79

79:                                               ; preds = %68, %76
  %80 = phi i8 [ %78, %76 ], [ 0, %68 ]
  %81 = add nuw nsw i8 %73, %80
  br i1 %18, label %96, label %82

82:                                               ; preds = %79
  %83 = load i8*, i8** %19, align 8, !tbaa !5
  %84 = and i64 %53, 4294967295
  %85 = getelementptr inbounds i8, i8* %83, i64 %84
  %86 = load i8, i8* %85, align 1, !tbaa !13, !range !15
  %87 = add nuw nsw i8 %81, %86
  %88 = getelementptr inbounds i8, i8* %83, i64 %52
  %89 = load i8, i8* %88, align 1, !tbaa !13, !range !15
  %90 = add nuw nsw i8 %87, %89
  %91 = select i1 %75, i1 true, i1 %18
  br i1 %91, label %96, label %92

92:                                               ; preds = %82
  %93 = load i8*, i8** %19, align 8, !tbaa !5
  %94 = getelementptr inbounds i8, i8* %93, i64 %74
  %95 = load i8, i8* %94, align 1, !tbaa !13, !range !15
  br label %96

96:                                               ; preds = %79, %82, %92
  %97 = phi i8 [ %90, %92 ], [ %90, %82 ], [ %81, %79 ]
  %98 = phi i8 [ %95, %92 ], [ 0, %82 ], [ 0, %79 ]
  %99 = add nuw nsw i8 %97, %98
  %100 = getelementptr inbounds i8, i8* %20, i64 %52
  %101 = load i8, i8* %100, align 1, !tbaa !13, !range !15
  %102 = icmp eq i8 %101, 0
  %103 = getelementptr inbounds i8, i8* %22, i64 %52
  %104 = icmp ugt i8 %99, 2
  %105 = and i8 %99, -2
  %106 = icmp eq i8 %105, 2
  %107 = select i1 %102, i1 %104, i1 %106
  %108 = zext i1 %107 to i8
  store i8 %108, i8* %103, align 1, !tbaa !13
  %109 = icmp eq i64 %74, %7
  br i1 %109, label %49, label %51, !llvm.loop !25
}

; Function Attrs: mustprogress noreturn uwtable
define dso_local void @_Z3appv() local_unnamed_addr #10 {
  %1 = load i32, i32* @WORLD_SIZE, align 4, !tbaa !9
  %2 = icmp sgt i32 %1, 0
  br i1 %2, label %3, label %5

3:                                                ; preds = %0
  %4 = tail call i32 @rand() #12
  unreachable

5:                                                ; preds = %0
  tail call void @_Z9drawWorldPPb(i8** noundef null)
  br label %6

6:                                                ; preds = %6, %5
  tail call void @_Z11updateWorldPPbS0_(i8** noundef null, i8** noundef null)
  tail call void @_Z9drawWorldPPb(i8** noundef null)
  tail call void @_Z11updateWorldPPbS0_(i8** noundef null, i8** noundef null)
  tail call void @_Z9drawWorldPPb(i8** noundef null)
  br label %6, !llvm.loop !27
}

; Function Attrs: uwtable
define internal void @_GLOBAL__sub_I_app.cpp() #11 section ".text.startup" {
  tail call void @_ZNSt8ios_base4InitC1Ev(%"class.std::ios_base::Init"* noundef nonnull align 1 dereferenceable(1) @_ZStL8__ioinit)
  %1 = tail call i32 @__cxa_atexit(void (i8*)* bitcast (void (%"class.std::ios_base::Init"*)* @_ZNSt8ios_base4InitD1Ev to void (i8*)*), i8* getelementptr inbounds (%"class.std::ios_base::Init", %"class.std::ios_base::Init"* @_ZStL8__ioinit, i64 0, i32 0), i8* nonnull @__dso_handle) #12
  ret void
}

attributes #0 = { "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nofree nounwind }
attributes #3 = { mustprogress uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { argmemonly mustprogress nofree nosync nounwind willreturn }
attributes #5 = { noreturn nounwind "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { mustprogress nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #7 = { mustprogress nofree norecurse nosync nounwind readonly uwtable willreturn "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #8 = { mustprogress nofree norecurse nosync nounwind uwtable willreturn writeonly "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #9 = { mustprogress nofree norecurse nosync nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #10 = { mustprogress noreturn uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #11 = { uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #12 = { nounwind }
attributes #13 = { noreturn nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!5 = !{!6, !6, i64 0}
!6 = !{!"any pointer", !7, i64 0}
!7 = !{!"omnipotent char", !8, i64 0}
!8 = !{!"Simple C++ TBAA"}
!9 = !{!10, !10, i64 0}
!10 = !{!"int", !7, i64 0}
!11 = distinct !{!11, !12}
!12 = !{!"llvm.loop.mustprogress"}
!13 = !{!14, !14, i64 0}
!14 = !{!"bool", !7, i64 0}
!15 = !{i8 0, i8 2}
!16 = !{!17, !10, i64 0}
!17 = !{!"_ZTS8SDL_Rect", !10, i64 0, !10, i64 4, !10, i64 8, !10, i64 12}
!18 = !{!17, !10, i64 4}
!19 = !{!17, !10, i64 8}
!20 = !{!17, !10, i64 12}
!21 = distinct !{!21, !12}
!22 = distinct !{!22, !12}
!23 = distinct !{!23, !12}
!24 = distinct !{!24, !12}
!25 = distinct !{!25, !12, !26}
!26 = !{!"llvm.loop.peeled.count", i32 1}
!27 = distinct !{!27, !12}
