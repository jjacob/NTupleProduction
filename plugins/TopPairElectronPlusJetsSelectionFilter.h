#ifndef BristolTopPairElectronPlusJetsSelectionFilter
#define BristolTopPairElectronPlusJetsSelectionFilter

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include <boost/array.hpp>
#include <string>

namespace TTbarEPlusJetsReferenceSelection {
enum Step {
	AllEvents,
	EventCleaningAndTrigger,
	OneIsolatedElectron,
	LooseMuonVeto,
	DiLeptonVeto,
	ConversionVeto,
	AtLeastOneGoodJet,
	AtLeastTwoGoodJets,
	AtLeastThreeGoodJets,
	AtLeastFourGoodJets,
	AtLeastOneBtag,
	AtLeastTwoBtags,
	NUMBER_OF_SELECTION_STEPS
};

const std::string StringSteps[NUMBER_OF_SELECTION_STEPS] = { //
		"AllEvents", //
				"EventCleaningAndTrigger", //
				"OneIsolatedElectron", //
				"LooseMuonVeto", //
				"DiLeptonVeto", //
				"ConversionVeto", //
				"AtLeastOneGoodJet", //
				"AtLeastTwoGoodJets", //
				"AtLeastThreeGoodJets", //
				"AtLeastFourGoodJets", //
				"AtLeastOneBtag", //
				"AtLeastTwoBtags" //
		};
}

class TopPairElectronPlusJetsSelectionFilter: public edm::EDFilter {
public:
	explicit TopPairElectronPlusJetsSelectionFilter(const edm::ParameterSet&);
	virtual ~TopPairElectronPlusJetsSelectionFilter();

	virtual void beginJob();
	virtual bool filter(edm::Event&, const edm::EventSetup&);
	virtual void endJob();
	virtual bool beginRun(edm::Run &, const edm::EventSetup &);

	static void fillDescriptions(edm::ConfigurationDescriptions & descriptions);

	virtual bool isGoodJet(const pat::Jet& jet) const;
	virtual bool isGoodElectron(const pat::Electron& electron) const;

	//definitions of loose objects
	virtual bool isLooseElectron(const pat::Electron& electron) const;
	virtual bool isLooseMuon(const pat::Muon& muon) const;
	//isolation definitions
//	virtual double getRelativeIsolation(const pat::Electron& electron) const;
//	virtual double getRelativeIsolation(const pat::Muon& muon) const;
	virtual void getLooseElectrons();
	virtual void getLooseMuons();
	virtual void goodIsolatedElectrons();
	virtual void cleanedJets();
	virtual void cleanedBJets();

	virtual bool passesSelectionStep(edm::Event& iEvent, unsigned int selectionStep) const;

	virtual bool passesEventCleaning(edm::Event& iEvent) const;
	virtual bool passesScrapingVeto(edm::Event& event) const;
	virtual bool passesTriggerSelection() const;
	virtual bool hasExactlyOneIsolatedLepton() const;
	virtual bool passesLooseLeptonVeto() const;
	virtual bool passesDileptonVeto() const;
	virtual bool passesConversionVeto() const;
	virtual bool hasAtLeastOneGoodJet() const;
	virtual bool hasAtLeastTwoGoodJets() const;
	virtual bool hasAtLeastThreeGoodJets() const;
	virtual bool hasAtLeastFourGoodJets() const;
	virtual bool hasExactlyZeroGoodBJet() const;
	virtual bool hasExactlyOneGoodBJet() const;
	virtual bool hasAtLeastOneGoodBJet() const;
	virtual bool hasAtLeastTwoGoodBJets() const;

private:
	virtual void setupEventContent(edm::Event& iEvent);

	//config
	edm::InputTag jetInput_, electronInput_, muonInput_, hltInputTag_, VertexInput_, trkInput_, hcalNoiseInput_;
	edm::InputTag hcalLaserFilterInput_, ecalDeadCellFilterInput_, ecalLaserCorrFilterInput_, manystripclus53X_, toomanystripclus53X_, logErrorTooManyClusters_, trackingFailureFilter_, eeBadScFilter_;

	double min1JetPt_, min2JetPt_, min3JetPt_, min4JetPt_;

	double tightElectronIso_, controlElectronIso_, looseElectronIso_, looseMuonIso_;
	bool useDeltaBetaCorrectionsForMuons_, useDeltaBetaCorrectionsForElectrons_, useRhoActiveAreaCorrections_, useMETFilters_, useEEBadScFilter_, tagAndProbeStudies_, dropTriggerSelection_;

	std::string prefix_, MCSampleTag_;

	bool debug_, taggingMode_, bSelectionInTaggingMode_;

	// Control region selections
	bool nonIsolatedElectronSelection_;
	bool invertedConversionSelection_;

	//internal
	boost::array<bool, TTbarEPlusJetsReferenceSelection::NUMBER_OF_SELECTION_STEPS> passes_;
	unsigned int runNumber_, signalElectronIndex_;
	bool isRealData_, hasSignalElectron_;
	double rho_;
	pat::JetCollection jets_, cleanedJets_, cleanedBJets_;
	pat::ElectronCollection electrons_, goodIsolatedElectrons_, looseElectrons_;
	pat::MuonCollection muons_, looseMuons_;
	pat::Electron signalElectron_;
	HLTConfigProvider hltConfig_;
	edm::TriggerResults triggerResults_;

};

#endif

