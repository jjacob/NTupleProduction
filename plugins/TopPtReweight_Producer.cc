#include "BristolAnalysis/NTupleTools/plugins/TopPtReweight_Producer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"

using namespace edm;
using namespace std;

TopPtReweight_Producer::TopPtReweight_Producer(const edm::ParameterSet& iConfig) :
		gen_event_input_(iConfig.getParameter < InputTag > ("gen_event_input")),
		prefix_(iConfig.getParameter < string > ("prefix")),
		TopPtSystematic_(iConfig.getParameter<int>("TopPtSystematic")) {
		produces <double>();
}

void TopPtReweight_Producer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

	std::vector<double> topPtWeights;
	double topPtReweight(1.0);
	double leptonicTopPt = 0.0;
	double hadronicTopPt = 0.0;
	double scaleFactorLeptonicTop = 0.0;
	double scaleFactorHadronicTop = 0.0;

	//carry out top pt reweighting only if monte carlo
	if (!iEvent.isRealData()) {
		//get the generated event
		edm::Handle < TtGenEvent > genEvt;
		iEvent.getByLabel(gen_event_input_, genEvt);
		if (genEvt -> leptonicDecayTop()) {
			leptonicTopPt = genEvt -> leptonicDecayTop() -> pt();
		}
		if (genEvt -> hadronicDecayTop()) {
			hadronicTopPt = genEvt -> hadronicDecayTop() -> pt();
		}

		// calculate scale factors (using info from:
		// https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting#MC_SFs_Reweighting)
		scaleFactorLeptonicTop = 0.159 - 0.00141*leptonicTopPt;
		scaleFactorHadronicTop = 0.159 - 0.00141*hadronicTopPt;

		std::cout << "scaleFactorLeptonicTop = " << scaleFactorLeptonicTop << endl;
		std::cout << "scaleFactorHadronicTop = " << scaleFactorHadronicTop << endl;

		topPtReweight = sqrt(scaleFactorLeptonicTop * scaleFactorHadronicTop);

		std::cout << "topPtReweight = " << topPtReweight << endl;

	std::auto_ptr<double> topPtReweightPointer(new double(topPtReweight));
	iEvent.put(topPtReweightPointer);

	}
}

void TopPtReweight_Producer::fillDescriptions(edm::ConfigurationDescriptions & descriptions) {
	edm::ParameterSetDescription desc;
	desc.add < InputTag > ("genEvt");
	desc.add < string > ("TopPtReweights");
	desc.add < int > ("TopPtSystematic");

	descriptions.add("TopPtReweight_Producer", desc);
}


DEFINE_FWK_MODULE (TopPtReweight_Producer);
