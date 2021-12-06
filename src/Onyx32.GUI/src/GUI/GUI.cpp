module onyx32.gui;

namespace Onyx32::GUI
{
	class TestImplement : public ICoreFactory
	{
		public:
			virtual ~TestImplement();
			virtual int Blah() override;
	};

	TestImplement::~TestImplement() {}
	int TestImplement::Blah() { return 1; }

	ICoreFactory* GetCoreFactory()
	{
		return new TestImplement();
	}
}