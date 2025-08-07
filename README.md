# Unreal Engine Portfolio

## 프로젝트 소개  
언리얼 엔진5 기반으로 개발된 개인 미니 UI 포트폴리오 프로젝트입니다.  
UMG 기반 위젯을 C++로 구조화하고 **데이터 기반 필터링 및 정렬, 강화, 제작** 등의 컨텐츠들을 구현하였습니다.  

📽[포트폴리오 영상](https://www.youtube.com/watch?v=6dWpDaXHGjc&feature=youtu.be)

## 주요 특징  
- 데이터 기반 UI 처리  
- 재사용 및 확장을 고려한 위젯 구조 설계  
- TileView + Wrapper 기반의 동적 UI 리스트 구성  
- 블루프린트와 C++ 간의 역할 분리 및 협업 고려
- 유지 보수와 기능 확장을 고려한 클래스 구조 설계  

## 개발 환경
- Unreal Engine 5.5
- Blueprint
- Visual Studio 2022
- C++

## 구현 기능 요약
- 캐릭터, 인벤토리, 상점 항목을 TileView로 동적 출력
- Enum 기반 필터 UI 및 카테고리 필터링 처리
- 캐릭터 레벨 변경 시 Delegate 기반 실시간 UI 갱신
- 강화 성공/실패에 따른 애니메이션 출력
- 제작 : 아이템 선택 > 재료 확인 > 제작 진행까지의 플로우 처리
