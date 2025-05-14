# DirectXGame

DirectX 11 을 사용하여 만든 게임 엔진입니다.

Cmake 를 사용하여 빌드할 수 있습니다.

- C++17 이상
- Visual Studio 2017 이상
- Cmake 3.10 이상

구조는 다음과 같습니다.

- Assets: 텍스처, 모델 파일 등 에셋을 포함합니다.
- Include: 헤더 파일을 포함합니다.
- Lib: 라이브러리 파일을 포함합니다.
- Source: C++ 소스 파일을 포함합니다.
- Resource: 윈도우 리소스 파일을 포함합니다.

![image](https://github.com/user-attachments/assets/5714e0e3-fc57-461a-a841-0f41253d49f1)

## Include

### Core

App 클래스와 Timer 클래스를 포함합니다.

- **App**: 윈도우 창, DirectX, 타이머, 씬 등을 초기화합니다. 메인 루프에서 윈도우 이벤트 처리, 타이머 처리, 씬 업데이트, 렌더링 등이 이루어집니다.
- Timer: 총 시간과 프레임 간 delta time 을 업데이트합니다.

### External

모델과 텍스처 로드 등에 필요한 외부 라이브러리를 포함합니다.

- tiny_obj_loader: obj 파일을 로드합니다.
- DirectXTex: 이미지 파일을 로드합니다.

### Graphics

장치 초기화 및 렌더링을 수행하기 위한 클래스를 포함합니다.

- **Divice**: DirectX 를 초기화합니다.
- **Context**: Context 를 소유합니다.
- **SwapChain**: Swap Chain 을 초기화하고 소유합니다.
- FrameBuffer: RenderTargetView, DepthStencilView 를 초기화하고 소유하는 클래스입니다.
- Viewport: Viewport 를 초기화합니다.
- Sampler: Sampler 를 초기화합니다.

- Vertex: Vertex struct 를 정의합니다. Vertex 는 position, normal, texcoord, color 등을 가집니다.
- VertexBuffer: 정점 버퍼를 소유하는 클래스입니다.
- IndexBuffer: 인덱스 버퍼를 소유하는 클래스입니다.
- **ConstantBuffer**: MatrixBuffer, LightBuffer, MaterialBuffer, CameraBuffer 등 상수 버퍼를 추상화한 클래스입니다.

- VertexShader: Vertex Shader 를 초기화하고 소유합니다.
- PixelShader: Pixel Shader 를 초기화하고 소유합니다.
- InputLayout: InputLayout 을 초기화하고 소유합니다.
  
- **Renderer**: Scene 을 파라미터로 받아서 Camera, Light 등을 세팅하고 Entity 별로 Mesh, Material 등을 바인드합니다.

### Input

사용자 입력을 저장하고 처리하는 클래스를 포함합니다.

- **InputSystem**: Window Procedure 에서 입력을 받고 이를 저장합니다. 입력은 Raw Input 을 사용합니다.
- InputListener: Observer 패턴을 사용하기 위한 Listener 를 정의합니다.
- Keyboard: 사용자의 키보드 입력을 저장하는 클래스입니다. key state 를 저장합니다.
- Mouse: 사용자의 마우스 입력을 저장하는 클래스입니다.

### Resource

Mesh, Material 등의 자원을 관리하는 클래스를 포함합니다.

- **Mesh**: 정점 배열과 인덱스 배열을 파라미터로 받아서 정점 버퍼와 인덱스 버퍼를 구성합니다.
- **Material**: 쉐이더, 텍스처, 머티리얼 속성 등을 모아 놓은 클래스입니다.
- Texture: 텍스처를 생성하고 소유하는 클래스입니다.
- Shader: Shader 들을 생성하고 소유하는 클래스입니다.

- IResourceLoader: Loader 들을 추상화한 클래스입니다.
- ResourceDescriptor: Resource 의 id, name, type, path 등 정보를 기술한 구조체입니다.

- MeshLoader: TinyObjLoader 를 바탕으로 OBJ 파일을 로드합니다.
- TextureLoader: DirectXTex 를 바탕으로 이미지 파일을 로드합니다.
- ShaderLoader: 쉐이더를 로드합니다.

### Scene

Entity, Component 등 씬과 관련 있는 클래스를 포함합니다.

- **Entity**: Component 들을 담는 클래스입니다.
- **Component**: TransformComponent, MeshComponent, MaterialComponent 등 다양한 Component 들의 상위 클래스입니다.

- **Scene**: 씬 구성과 관련된 Camera, Light, Entities 정보를 저장합니다.

- Camera: 카메라의 위치와 회전을 세팅하고 입력에 따라 카메라의 변화를 업데이트합니다.
- Light: 조명 정보를 세팅하고 업데이트합니다.

### Window

윈도우를 표시하기 위한 클래스를 포함합니다.

- **Window**: 윈도우 클래스를 등록하고 창을 띄우는 클래스입니다.

## Assets

### Models

모델 파일을 저장합니다.

- cottage: [Abandoned Cottage House](https://free3d.com/3d-model/abandoned-cottage-house-825251.html) 모델입니다.
- watchtower: [Watch Tower made of Wood](https://free3d.com/3d-model/watch-tower-made-of-wood-94934.html) 모델입니다.

### Shaders

쉐이더 파일을 저장합니다.

- VertexShader: 정점 쉐이더를 기술합니다. Matrix Buffer 를 바탕으로 삼각형을 clip space 로 옮깁니다.
- PixelShader: 픽셀 쉐이더를 기술합니다. [Blinn–Phong reflection model](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model) 을 사용해서 조명을 처리합니다.
- ShaderCommon: 쉐이더 파일에서 공통적으로 쓰이는 버퍼와 구조체를 정의합니다.
